/**
 * @file
 * @author Steve Karg
 * @date 2006
 * @brief Analog Value objects, customize for your use
 *
 * @section DESCRIPTION
 *
 * The Analog Value object is an object with a present-value that
 * uses a 'float' data type.
 *
 * @section LICENSE
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "bacnet/bacdef.h"
#include "bacnet/bacdcode.h"
#include "bacnet/bacenum.h"
#include "bacnet/bacapp.h"
#include "bacnet/config.h"
#include "bacnet/wp.h"
#include "bacnet/basic/services.h"
/* object - me! */
#include "bacnet/basic/object/av.h"

struct av_object_data {
    const uint32_t object_id;
    const char *object_name;
    uint16_t units;
    const float min_value;
    const float max_value;
    const bool writable : 1;
    bool out_of_service : 1;
    float value;
};
/* default values */
static struct av_object_data Object_List[] = {
    { 1, "Control Signal Minimum", UNITS_VOLTS, 0.0, 10.0, true, false, 0.0 },
    { 2, "Control Signal Maximum", UNITS_VOLTS, 0.0, 10.0, true, false, 0.0 },
    { 0, NULL, UNITS_NO_UNITS, 0.0, 0.0, false, false, 0.0 }
};
/* number of objects - set by init after counting names */
static unsigned Analog_Value_Objects_Max;

/* These three arrays are used by the ReadPropertyMultiple handler */
static const int Analog_Value_Properties_Required[] = { PROP_OBJECT_IDENTIFIER,
    PROP_OBJECT_NAME, PROP_OBJECT_TYPE, PROP_PRESENT_VALUE, PROP_STATUS_FLAGS,
    PROP_EVENT_STATE, PROP_OUT_OF_SERVICE, PROP_UNITS, -1 };

static const int Analog_Value_Properties_Optional[]
    = { PROP_MIN_PRES_VALUE, PROP_MAX_PRES_VALUE, -1 };

static const int Analog_Value_Properties_Proprietary[] = { -1 };

void Analog_Value_Property_Lists(
    const int **pRequired, const int **pOptional, const int **pProprietary)
{
    if (pRequired)
        *pRequired = Analog_Value_Properties_Required;
    if (pOptional)
        *pOptional = Analog_Value_Properties_Optional;
    if (pProprietary)
        *pProprietary = Analog_Value_Properties_Proprietary;

    return;
}

/**
 * Return the object or NULL if not found.
 *
 * @param  object_instance - object-instance number of the object
 *
 * @return  object if the instance is found, and NULL if not
 */
static struct av_object_data *Object_List_Element(uint32_t object_instance)
{
    unsigned index;

    while (Analog_Value_Objects_Max == 0) {
        Analog_Value_Init();
    }
    for (index = 0; index < Analog_Value_Objects_Max; index++) {
        if (Object_List[index].object_id == object_instance) {
            return &Object_List[index];
        }
    }

    return NULL;
}

/**
 * Determines if a given Analog Value instance is valid
 *
 * @param  object_instance - object-instance number of the object
 *
 * @return  true if the instance is valid, and false if not
 */
bool Analog_Value_Valid_Instance(uint32_t object_instance)
{
    if (Object_List_Element(object_instance)) {
        return true;
    }

    return false;
}

/**
 * Determines the number of Analog Value objects
 *
 * @return  Number of Analog Value objects
 */
unsigned Analog_Value_Count(void)
{
    return Analog_Value_Objects_Max;
}

/**
 * Determines the object instance-number for a given 0..N index
 * of Analog Value objects where N is Analog_Value_Count().
 *
 * @param  index - 0..N value
 *
 * @return  object instance-number for the given index
 */
uint32_t Analog_Value_Index_To_Instance(unsigned index)
{
    uint32_t object_instance = UINT32_MAX;

    if (index < Analog_Value_Objects_Max) {
        object_instance = Object_List[index].object_id;
    }

    return object_instance;
}

/**
 * For a given object instance-number, determines a 0..N index
 * of Analog Value objects where N is Analog_Value_Count().
 *
 * @param  object_instance - object-instance number of the object
 *
 * @return  index for the given instance-number, or N if not valid.
 */
unsigned Analog_Value_Instance_To_Index(uint32_t object_instance)
{
    unsigned index = 0;

    for (index = 0; index < Analog_Value_Objects_Max; index++) {
        if (Object_List[index].object_id == object_instance) {
            break;
        }
    }

    return index;
}

/**
 * For a given object instance-number, determines the present-value
 *
 * @param  object_instance - object-instance number of the object
 *
 * @return  present-value of the object
 */
float Analog_Value_Present_Value(uint32_t object_instance)
{
    float value = 0;
    struct av_object_data *pObject;

    pObject = Object_List_Element(object_instance);
    if (pObject) {
        value = pObject->value;
    }

    return value;
}

/**
 * For a given object instance-number, sets the present-value
 *
 * @param  object_instance - object-instance number of the object
 * @param  value - floating point analog value
 *
 * @return  true if values are within range and present-value is set.
 */
bool Analog_Value_Present_Value_Set(
    uint32_t object_instance, float value, uint8_t priority)
{
    bool status = false;
    struct av_object_data *pObject;

    pObject = Object_List_Element(object_instance);
    if (pObject) {
        if (!pObject->out_of_service) {
            pObject->value = value;
            status = true;
        }
    }

    return status;
}

/**
 * For a given object instance-number, writes the present-value
 *
 * @param  object_instance - object-instance number of the object
 * @param  value - enumerated binary present-value
 *
 * @return  true if values are within range and present-value is writable.
 */
static bool Analog_Value_Present_Value_Write(uint32_t object_instance,
    float value,
    BACNET_ERROR_CLASS *error_class,
    BACNET_ERROR_CODE *error_code)
{
    bool status = false;
    struct av_object_data *pObject;

    pObject = Object_List_Element(object_instance);
    if (pObject) {
        if (pObject->writable || pObject->out_of_service) {
            if ((value >= pObject->min_value)
                && (value <= pObject->max_value)) {
                pObject->value = value;
                status = true;
            } else {
                *error_class = ERROR_CLASS_PROPERTY;
                *error_code = ERROR_CODE_VALUE_OUT_OF_RANGE;
            }
        } else {
            *error_class = ERROR_CLASS_PROPERTY;
            *error_code = ERROR_CODE_WRITE_ACCESS_DENIED;
        }
    }

    return status;
}

/**
 * For a given object instance-number, determines the min-pres-value
 *
 * @param  object_instance - object-instance number of the object
 *
 * @return  min-pres-value of the object
 */
static float Analog_Value_Min_Pres_Value(uint32_t object_instance)
{
    float value = 0.0;
    struct av_object_data *pObject;

    pObject = Object_List_Element(object_instance);
    if (pObject) {
        value = pObject->min_value;
    }

    return value;
}

/**
 * For a given object instance-number, determines the max-pres-value
 *
 * @param  object_instance - object-instance number of the object
 *
 * @return  max-pres-value of the object
 */
static float Analog_Value_Max_Pres_Value(uint32_t object_instance)
{
    float value = 0.0;
    struct av_object_data *pObject;

    pObject = Object_List_Element(object_instance);
    if (pObject) {
        value = pObject->max_value;
    }

    return value;
}

/**
 * @brief For a given object instance-number, determines the object-name
 * @param  object_instance - object-instance number of the object
 * @return  true if the object-name was retrieved.
 */
bool Analog_Value_Object_Name(
    uint32_t object_instance, BACNET_CHARACTER_STRING *object_name)
{
    bool status = false;
    struct av_object_data *pObject;

    pObject = Object_List_Element(object_instance);
    if (pObject) {
        status = characterstring_init_ansi(object_name, pObject->object_name);
    }

    return status;
}

/**
 * @brief For a given object instance-number, determines the units
 * @param  object_instance - object-instance number of the object
 * @return units from the given object, or UNITS_NO_UNITS if not found
 */
uint16_t Analog_Value_Units(uint32_t object_instance)
{
    uint16_t units = UNITS_NO_UNITS;
    struct av_object_data *pObject;

    pObject = Object_List_Element(object_instance);
    if (pObject) {
        units = pObject->units;
    }

    return units;
}

/**
 * @brief For a given object instance-number, sets the units
 * @param  object_instance - object-instance number of the object
 * @param  units - property value to set
 * @return true if valid instance and property was set
 */
bool Analog_Value_Units_Set(uint32_t object_instance, uint16_t units)
{
    bool status = false;
    struct av_object_data *pObject;

    pObject = Object_List_Element(object_instance);
    if (pObject) {
        pObject->units = units;
        status = true;
    }

    return status;
}

/**
 * For a given object instance-number, returns the out-of-service
 * property value
 *
 * @param  object_instance - object-instance number of the object
 *
 * @return  out-of-service property value
 */
bool Analog_Value_Out_Of_Service(uint32_t object_instance)
{
    bool value = false;
    struct av_object_data *pObject;

    pObject = Object_List_Element(object_instance);
    if (pObject) {
        value = pObject->out_of_service;
    }

    return value;
}

/**
 * For a given object instance-number, sets the out-of-service property value
 *
 * @param object_instance - object-instance number of the object
 * @param value - boolean out-of-service value
 *
 * @return true if the out-of-service property value was set
 */
void Analog_Value_Out_Of_Service_Set(uint32_t object_instance, bool value)
{
    struct av_object_data *pObject;

    pObject = Object_List_Element(object_instance);
    if (pObject) {
        pObject->out_of_service = value;
    }
}

/* return apdu len, or -1 on error */
int Analog_Value_Read_Property(BACNET_READ_PROPERTY_DATA *rpdata)
{
    int apdu_len = 0; /* return value */
    BACNET_BIT_STRING bit_string;
    float real_value = 1.414F;
    BACNET_CHARACTER_STRING char_string = { 0 };
    uint8_t *apdu = NULL;
    uint16_t units = UNITS_NO_UNITS;

    if ((rpdata->application_data == NULL)
        || (rpdata->application_data_len == 0)) {
        return 0;
    }
    apdu = rpdata->application_data;
    switch (rpdata->object_property) {
        case PROP_OBJECT_IDENTIFIER:
            apdu_len = encode_application_object_id(
                &apdu[0], rpdata->object_type, rpdata->object_instance);
            break;
        case PROP_OBJECT_NAME:
            Analog_Value_Object_Name(rpdata->object_instance, &char_string);
            apdu_len
                = encode_application_character_string(&apdu[0], &char_string);
            break;
        case PROP_OBJECT_TYPE:
            apdu_len
                = encode_application_enumerated(&apdu[0], rpdata->object_type);
            break;
        case PROP_PRESENT_VALUE:
            real_value = Analog_Value_Present_Value(rpdata->object_instance);
            apdu_len = encode_application_real(&apdu[0], real_value);
            break;
        case PROP_MIN_PRES_VALUE:
            apdu_len = encode_application_real(
                &apdu[0], Analog_Value_Min_Pres_Value(rpdata->object_instance));
            break;
        case PROP_MAX_PRES_VALUE:
            apdu_len = encode_application_real(
                &apdu[0], Analog_Value_Max_Pres_Value(rpdata->object_instance));
            break;
        case PROP_STATUS_FLAGS:
            bitstring_init(&bit_string);
            bitstring_set_bit(&bit_string, STATUS_FLAG_IN_ALARM, false);
            bitstring_set_bit(&bit_string, STATUS_FLAG_FAULT, false);
            bitstring_set_bit(&bit_string, STATUS_FLAG_OVERRIDDEN, false);
            bitstring_set_bit(&bit_string, STATUS_FLAG_OUT_OF_SERVICE,
                Analog_Value_Out_Of_Service(rpdata->object_instance));
            apdu_len = encode_application_bitstring(&apdu[0], &bit_string);
            break;
        case PROP_EVENT_STATE:
            apdu_len
                = encode_application_enumerated(&apdu[0], EVENT_STATE_NORMAL);
            break;
        case PROP_OUT_OF_SERVICE:
            apdu_len = encode_application_boolean(&apdu[0],
                Analog_Value_Out_Of_Service(rpdata->object_instance));
            break;
        case PROP_UNITS:
            units = Analog_Value_Units(rpdata->object_instance);
            apdu_len = encode_application_enumerated(&apdu[0], units);
            break;
        default:
            rpdata->error_class = ERROR_CLASS_PROPERTY;
            rpdata->error_code = ERROR_CODE_UNKNOWN_PROPERTY;
            apdu_len = BACNET_STATUS_ERROR;
            break;
    }
    /*  only array properties can have array options */
    if ((apdu_len >= 0) && (rpdata->array_index != BACNET_ARRAY_ALL)) {
        rpdata->error_class = ERROR_CLASS_PROPERTY;
        rpdata->error_code = ERROR_CODE_PROPERTY_IS_NOT_AN_ARRAY;
        apdu_len = BACNET_STATUS_ERROR;
    }

    return apdu_len;
}

/* returns true if successful */
bool Analog_Value_Write_Property(BACNET_WRITE_PROPERTY_DATA *wp_data)
{
    bool status = false; /* return value */
    BACNET_APPLICATION_DATA_VALUE value;
    int len = 0;

    /* decode the some of the request */
    len = bacapp_decode_application_data(
        wp_data->application_data, wp_data->application_data_len, &value);
    /* FIXME: len < application_data_len: more data? */
    if (len < 0) {
        /* error while decoding - a value larger than we can handle */
        wp_data->error_class = ERROR_CLASS_PROPERTY;
        wp_data->error_code = ERROR_CODE_VALUE_OUT_OF_RANGE;
        return false;
    }
    if ((wp_data->object_property != PROP_PRIORITY_ARRAY)
        && (wp_data->array_index != BACNET_ARRAY_ALL)) {
        /*  only array properties can have array options */
        wp_data->error_class = ERROR_CLASS_PROPERTY;
        wp_data->error_code = ERROR_CODE_PROPERTY_IS_NOT_AN_ARRAY;
        return false;
    }
    switch (wp_data->object_property) {
        case PROP_PRESENT_VALUE:
            status = WPValidateArgType(&value, BACNET_APPLICATION_TAG_REAL,
                &wp_data->error_class, &wp_data->error_code);
            if (status) {
                status = Analog_Value_Present_Value_Write(
                    wp_data->object_instance, value.type.Real,
                    &wp_data->error_class, &wp_data->error_code);
            }
            break;
        case PROP_OUT_OF_SERVICE:
            status = WPValidateArgType(&value, BACNET_APPLICATION_TAG_BOOLEAN,
                &wp_data->error_class, &wp_data->error_code);
            if (status) {
                Analog_Value_Out_Of_Service_Set(
                    wp_data->object_instance, value.type.Boolean);
            }
            break;
        case PROP_UNITS:
        case PROP_OBJECT_IDENTIFIER:
        case PROP_OBJECT_NAME:
        case PROP_OBJECT_TYPE:
        case PROP_STATUS_FLAGS:
        case PROP_EVENT_STATE:
        case PROP_DESCRIPTION:
        case PROP_MIN_PRES_VALUE:
        case PROP_MAX_PRES_VALUE:
            wp_data->error_class = ERROR_CLASS_PROPERTY;
            wp_data->error_code = ERROR_CODE_WRITE_ACCESS_DENIED;
            break;
        case PROP_RELINQUISH_DEFAULT:
        default:
            wp_data->error_class = ERROR_CLASS_PROPERTY;
            wp_data->error_code = ERROR_CODE_UNKNOWN_PROPERTY;
            break;
    }
    /* not using len at this time */
    len = len;

    return status;
}

/**
 * Initializes the Analog Value object data
 */
void Analog_Value_Init(void)
{
    unsigned index = 0;

    while (Object_List[index].object_name) {
        index++;
    }
    Analog_Value_Objects_Max = index;
}
