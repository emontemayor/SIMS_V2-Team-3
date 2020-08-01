/**
 * @file
 * @author Steve Karg
 * @date 2015
 * @brief Multi-State Value objects, customize for your use
 *
 * @section DESCRIPTION
 *
 * The Multi-State object is an object with a present-value that
 * uses an integer data type with a sequence of 1 to N values.
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
#include <stdlib.h>
#include "bacnet/bacdef.h"
#include "bacnet/bacdcode.h"
#include "bacnet/bacenum.h"
#include "bacnet/bacapp.h"
#include "bacnet/config.h"
#include "bacnet/wp.h"
#include "bacnet/basic/services.h"
/* object - me! */
#include "bacnet/basic/object/msv.h"

static const char *Baud_Rate_State_Text[6]
    = { "9600", "19200", "38400", "57600", "76800", "115200" };

static const char *Temperature_Units_State_Text[2]
    = { "Celsius", "Fahrenheit" };

struct msv_object_data {
    const uint32_t object_id;
    const char *object_name;
    const char **state_text_list;
    const uint32_t max_states;
    const bool writable : 1;
    bool out_of_service : 1;
    uint32_t value;
};
static struct msv_object_data Object_List[] = {
    { 1, "Baud Rate", Baud_Rate_State_Text, 6, true, false, 3 },
    { 2, "Temperature Units", Temperature_Units_State_Text, 2, true, false, 1 },
    { 0, NULL, NULL, 0, false, false, 0 }
};
/* number of objects - set by init after counting names */
static unsigned Multistate_Value_Objects_Max;

/* These three arrays are used by the ReadPropertyMultiple handler*/
static const int Properties_Required[] = { PROP_OBJECT_IDENTIFIER,
    PROP_OBJECT_NAME, PROP_OBJECT_TYPE, PROP_PRESENT_VALUE, PROP_STATUS_FLAGS,
    PROP_EVENT_STATE, PROP_OUT_OF_SERVICE, PROP_NUMBER_OF_STATES, -1 };

static const int Properties_Optional[] = { PROP_STATE_TEXT, -1 };

static const int Properties_Proprietary[] = { -1 };

/**
 * Returns the list of required, optional, and proprietary properties.
 * Used by ReadPropertyMultiple service.
 *
 * @param pRequired - pointer to list of int terminated by -1, of
 * BACnet required properties for this object.
 * @param pOptional - pointer to list of int terminated by -1, of
 * BACnet optional properties for this object.
 * @param pProprietary - pointer to list of int terminated by -1, of
 * BACnet proprietary properties for this object.
 */
void Multistate_Value_Property_Lists(
    const int **pRequired, const int **pOptional, const int **pProprietary)
{
    if (pRequired)
        *pRequired = Properties_Required;
    if (pOptional)
        *pOptional = Properties_Optional;
    if (pProprietary)
        *pProprietary = Properties_Proprietary;

    return;
}

/**
 * Return the object or NULL if not found.
 *
 * @param  object_instance - object-instance number of the object
 *
 * @return  object if the instance is found, and NULL if not
 */
static struct msv_object_data *Object_List_Element(uint32_t object_instance)
{
    unsigned index;

    while (Multistate_Value_Objects_Max == 0) {
        Multistate_Value_Init();
    }
    for (index = 0; index < Multistate_Value_Objects_Max; index++) {
        if (Object_List[index].object_id == object_instance) {
            return &Object_List[index];
        }
    }

    return NULL;
}

/**
 * Determines if a given Multistate Input instance is valid
 *
 * @param  object_instance - object-instance number of the object
 *
 * @return  true if the instance is valid, and false if not
 */
bool Multistate_Value_Valid_Instance(uint32_t object_instance)
{
    if (Object_List_Element(object_instance)) {
        return true;
    }

    return false;
}

/**
 * Determines the number of Multistate Input objects
 *
 * @return  Number of Multistate Input objects
 */
unsigned Multistate_Value_Count(void)
{
    return Multistate_Value_Objects_Max;
}

/**
 * Determines the object instance-number for a given 0..N index
 * of Multistate Input objects where N is Multistate_Value_Count().
 *
 * @param  index - 0..Multistate_Value_Count() value
 *
 * @return  object instance-number for the given index
 */
uint32_t Multistate_Value_Index_To_Instance(unsigned index)
{
    uint32_t object_instance = UINT32_MAX;

    if (index < Multistate_Value_Objects_Max) {
        object_instance = Object_List[index].object_id;
    }

    return object_instance;
}

/**
 * For a given object instance-number, determines a 0..N index
 * of Multistate Input objects where N is Multistate_Value_Count().
 *
 * @param  object_instance - object-instance number of the object
 *
 * @return  index for the given instance-number, or Multistate_Value_Count()
 * if not valid.
 */
unsigned Multistate_Value_Instance_To_Index(uint32_t object_instance)
{
    unsigned index = 0;

    for (index = 0; index < Multistate_Value_Objects_Max; index++) {
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
uint32_t Multistate_Value_Present_Value(uint32_t object_instance)
{
    uint32_t value = 1;
    struct msv_object_data *pObject;

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
 * @param  value - integer multi-state value
 *
 * @return  true if values are within range and present-value is set.
 */
bool Multistate_Value_Present_Value_Set(
    uint32_t object_instance, uint32_t value)
{
    bool status = false;
    struct msv_object_data *pObject;

    pObject = Object_List_Element(object_instance);
    if (pObject) {
        if (!pObject->out_of_service) {
            if (value != pObject->value) {
                pObject->value = value;
            }
            status = true;
        }
    }

    return status;
}

/**
 * For a given object instance-number, writes the present-value
 *
 * @param  object_instance - object-instance number of the object
 * @param  value - unsignd present-value
 *
 * @return  true if values are within range and present-value is writable.
 */
static bool Multistate_Value_Present_Value_Write(uint32_t object_instance,
    uint32_t value,
    BACNET_ERROR_CLASS *error_class,
    BACNET_ERROR_CODE *error_code)
{
    bool status = false;
    struct msv_object_data *pObject;

    pObject = Object_List_Element(object_instance);
    if (pObject) {
        if (pObject->writable) {
            if ((value >= 1) && (value <= pObject->max_states)) {
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
 * For a given object instance-number, loads the object-name into
 * a characterstring. Note that the object name must be unique
 * within this device.
 *
 * @param  object_instance - object-instance number of the object
 * @param  object_name - holds the object-name retrieved
 *
 * @return  true if object-name was retrieved
 */
bool Multistate_Value_Object_Name(
    uint32_t object_instance, BACNET_CHARACTER_STRING *object_name)
{
    bool status = false;
    struct msv_object_data *pObject;

    pObject = Object_List_Element(object_instance);
    if (pObject) {
        status = characterstring_init_ansi(object_name, pObject->object_name);
    }

    return status;
}

/**
 * For a given object instance-number, returns the state-text in
 * a C string.
 *
 * @param  object_instance - object-instance number of the object
 * @param  state_index - state index number 1..M of the text requested
 * where M = Multistate_Value_Max_States
 *
 * @return  C string retrieved
 */
char *Multistate_Value_State_Text(
    uint32_t object_instance, uint32_t state_index)
{
    char *pName = NULL; /* return value */
    struct msv_object_data *pObject;

    pObject = Object_List_Element(object_instance);
    if (pObject) {
        if ((state_index > 0) && (state_index <= pObject->max_states)) {
            state_index--;
            pName = (char *)pObject->state_text_list[state_index];
        }
    }

    return pName;
}

/**
 * For a given object instance-number, determines number of states
 *
 * @param  object_instance - object-instance number of the object
 *
 * @return  number of states
 */
static uint32_t Multistate_Value_Max_States(uint32_t object_instance)
{
    struct msv_object_data *pObject;
    uint32_t max_states = 0;

    pObject = Object_List_Element(object_instance);
    if (pObject) {
        max_states = pObject->max_states;
    }

    return max_states;
}

/**
 * For a given object instance-number, returns the out-of-service
 * property value
 *
 * @param  object_instance - object-instance number of the object
 *
 * @return  out-of-service property value
 */
bool Multistate_Value_Out_Of_Service(uint32_t object_instance)
{
    bool value = false;
    struct msv_object_data *pObject;

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
void Multistate_Value_Out_Of_Service_Set(uint32_t object_instance, bool value)
{
    struct msv_object_data *pObject;

    pObject = Object_List_Element(object_instance);
    if (pObject) {
        pObject->out_of_service = value;
    }
}

/**
 * ReadProperty handler for this object.  For the given ReadProperty
 * data, the application_data is loaded or the error flags are set.
 *
 * @param  rpdata - BACNET_READ_PROPERTY_DATA data, including
 * requested data and space for the reply, or error response.
 *
 * @return number of APDU bytes in the response, or
 * BACNET_STATUS_ERROR on error.
 */
int Multistate_Value_Read_Property(BACNET_READ_PROPERTY_DATA *rpdata)
{
    int len = 0;
    int apdu_len = 0; /* return value */
    BACNET_BIT_STRING bit_string;
    BACNET_CHARACTER_STRING char_string;
    uint32_t present_value = 0;
    unsigned i = 0;
    uint32_t max_states = 0;
    uint8_t *apdu = NULL;

    if ((rpdata == NULL) || (rpdata->application_data == NULL)
        || (rpdata->application_data_len == 0)) {
        return 0;
    }
    apdu = rpdata->application_data;
    switch (rpdata->object_property) {
        case PROP_OBJECT_IDENTIFIER:
            apdu_len = encode_application_object_id(
                &apdu[0], OBJECT_MULTI_STATE_VALUE, rpdata->object_instance);
            break;
            /* note: Name and Description don't have to be the same.
               You could make Description writable and different */
        case PROP_OBJECT_NAME:
            Multistate_Value_Object_Name(rpdata->object_instance, &char_string);
            apdu_len
                = encode_application_character_string(&apdu[0], &char_string);
            break;
        case PROP_OBJECT_TYPE:
            apdu_len = encode_application_enumerated(
                &apdu[0], OBJECT_MULTI_STATE_VALUE);
            break;
        case PROP_PRESENT_VALUE:
            present_value
                = Multistate_Value_Present_Value(rpdata->object_instance);
            apdu_len = encode_application_unsigned(&apdu[0], present_value);
            break;
        case PROP_STATUS_FLAGS:
            /* note: see the details in the standard on how to use these */
            bitstring_init(&bit_string);
            bitstring_set_bit(&bit_string, STATUS_FLAG_IN_ALARM, false);
            bitstring_set_bit(&bit_string, STATUS_FLAG_FAULT, false);
            bitstring_set_bit(&bit_string, STATUS_FLAG_OVERRIDDEN, false);
            bitstring_set_bit(&bit_string, STATUS_FLAG_OUT_OF_SERVICE,
                Multistate_Value_Out_Of_Service(rpdata->object_instance));
            apdu_len = encode_application_bitstring(&apdu[0], &bit_string);
            break;
        case PROP_EVENT_STATE:
            /* note: see the details in the standard on how to use this */
            apdu_len
                = encode_application_enumerated(&apdu[0], EVENT_STATE_NORMAL);
            break;
        case PROP_OUT_OF_SERVICE:
            apdu_len = encode_application_boolean(&apdu[0],
                Multistate_Value_Out_Of_Service(rpdata->object_instance));
            break;
        case PROP_NUMBER_OF_STATES:
            apdu_len = encode_application_unsigned(&apdu[apdu_len],
                Multistate_Value_Max_States(rpdata->object_instance));
            break;
        case PROP_STATE_TEXT:
            if (rpdata->array_index == 0) {
                /* Array element zero is the number of elements in the array */
                apdu_len = encode_application_unsigned(&apdu[0],
                    Multistate_Value_Max_States(rpdata->object_instance));
            } else if (rpdata->array_index == BACNET_ARRAY_ALL) {
                /* if no index was specified, then try to encode the entire list
                 */
                /* into one packet. */
                max_states
                    = Multistate_Value_Max_States(rpdata->object_instance);
                for (i = 1; i <= max_states; i++) {
                    characterstring_init_ansi(&char_string,
                        Multistate_Value_State_Text(
                            rpdata->object_instance, i));
                    /* FIXME: this might go beyond MAX_APDU length! */
                    len = encode_application_character_string(
                        &apdu[apdu_len], &char_string);
                    /* add it if we have room */
                    if ((apdu_len + len) < MAX_APDU) {
                        apdu_len += len;
                    } else {
                        rpdata->error_class = ERROR_CLASS_SERVICES;
                        rpdata->error_code = ERROR_CODE_NO_SPACE_FOR_OBJECT;
                        apdu_len = BACNET_STATUS_ERROR;
                        break;
                    }
                }
            } else {
                max_states
                    = Multistate_Value_Max_States(rpdata->object_instance);
                if (rpdata->array_index <= max_states) {
                    characterstring_init_ansi(&char_string,
                        Multistate_Value_State_Text(
                            rpdata->object_instance, rpdata->array_index));
                    apdu_len = encode_application_character_string(
                        &apdu[0], &char_string);
                } else {
                    rpdata->error_class = ERROR_CLASS_PROPERTY;
                    rpdata->error_code = ERROR_CODE_INVALID_ARRAY_INDEX;
                    apdu_len = BACNET_STATUS_ERROR;
                }
            }
            break;
        default:
            rpdata->error_class = ERROR_CLASS_PROPERTY;
            rpdata->error_code = ERROR_CODE_UNKNOWN_PROPERTY;
            apdu_len = BACNET_STATUS_ERROR;
            break;
    }
    /*  only array properties can have array options */
    if ((apdu_len >= 0) && (rpdata->object_property != PROP_STATE_TEXT)
        && (rpdata->array_index != BACNET_ARRAY_ALL)) {
        rpdata->error_class = ERROR_CLASS_PROPERTY;
        rpdata->error_code = ERROR_CODE_PROPERTY_IS_NOT_AN_ARRAY;
        apdu_len = BACNET_STATUS_ERROR;
    }

    return apdu_len;
}

/**
 * WriteProperty handler for this object.  For the given WriteProperty
 * data, the application_data is loaded or the error flags are set.
 *
 * @param  wp_data - BACNET_WRITE_PROPERTY_DATA data, including
 * requested data and space for the reply, or error response.
 *
 * @return false if an error is loaded, true if no errors
 */
bool Multistate_Value_Write_Property(BACNET_WRITE_PROPERTY_DATA *wp_data)
{
    bool status = false; /* return value */
    int len = 0;
    BACNET_APPLICATION_DATA_VALUE value;

    /* decode the first chunk of the request */
    len = bacapp_decode_application_data(
        wp_data->application_data, wp_data->application_data_len, &value);
    /* len < application_data_len: extra data for arrays only */
    if (len < 0) {
        /* error while decoding - a value larger than we can handle */
        wp_data->error_class = ERROR_CLASS_PROPERTY;
        wp_data->error_code = ERROR_CODE_VALUE_OUT_OF_RANGE;
        return false;
    }
    if ((wp_data->object_property != PROP_STATE_TEXT)
        && (wp_data->array_index != BACNET_ARRAY_ALL)) {
        /*  only array properties can have array options */
        wp_data->error_class = ERROR_CLASS_PROPERTY;
        wp_data->error_code = ERROR_CODE_PROPERTY_IS_NOT_AN_ARRAY;
        return false;
    }
    switch (wp_data->object_property) {
        case PROP_PRESENT_VALUE:
            status
                = WPValidateArgType(&value, BACNET_APPLICATION_TAG_UNSIGNED_INT,
                    &wp_data->error_class, &wp_data->error_code);
            if (status) {
                status = Multistate_Value_Present_Value_Write(
                    wp_data->object_instance, value.type.Unsigned_Int,
                    &wp_data->error_class, &wp_data->error_code);
            }
            break;
        case PROP_OUT_OF_SERVICE:
            status = WPValidateArgType(&value, BACNET_APPLICATION_TAG_BOOLEAN,
                &wp_data->error_class, &wp_data->error_code);
            if (status) {
                Multistate_Value_Out_Of_Service_Set(
                    wp_data->object_instance, value.type.Boolean);
            }
            break;
        case PROP_OBJECT_NAME:
        case PROP_STATE_TEXT:
        case PROP_OBJECT_IDENTIFIER:
        case PROP_OBJECT_TYPE:
        case PROP_STATUS_FLAGS:
        case PROP_EVENT_STATE:
        case PROP_NUMBER_OF_STATES:
            wp_data->error_class = ERROR_CLASS_PROPERTY;
            wp_data->error_code = ERROR_CODE_WRITE_ACCESS_DENIED;
            break;
        default:
            wp_data->error_class = ERROR_CLASS_PROPERTY;
            wp_data->error_code = ERROR_CODE_UNKNOWN_PROPERTY;
            break;
    }

    return status;
}

/**
 * Initializes the object list
 */
void Multistate_Value_Init(void)
{
    unsigned index = 0;

    while (Object_List[index].object_name) {
        index++;
    }
    Multistate_Value_Objects_Max = index;
}
