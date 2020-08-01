/**
 * @file
 * @author Steve Karg
 * @date 2015
 * @brief Binary Value objects, customize for your use
 *
 * @section DESCRIPTION
 *
 * The Binary Value object is an object with a present-value that
 * uses an enumerated data type with a value of ACTIVE or INACTIVE
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
#include "bacnet/basic/object/bv.h"

struct bv_object_data {
    const uint32_t object_id;
    const char *object_name;
    const char *inactive_text;
    const char *active_text;
    const bool writable : 1;
    bool out_of_service : 1;
    bool value;
};
static struct bv_object_data Object_List[] = {
    { 1, "RF Output Enable", "Off", "On", false, false },
    { 2, "Control Voltage Enable", "Off", "On", false, false },
    { 0, NULL, NULL, NULL, false, false, false }
};
/* number of objects - set by init after counting names */
static unsigned Binary_Value_Objects_Max;

/* These three arrays are used by the ReadPropertyMultiple handler */
static const int Properties_Required[] = { PROP_OBJECT_IDENTIFIER,
    PROP_OBJECT_NAME, PROP_OBJECT_TYPE, PROP_PRESENT_VALUE, PROP_STATUS_FLAGS,
    PROP_EVENT_STATE, PROP_OUT_OF_SERVICE, -1 };

static const int Properties_Optional[]
    = { PROP_ACTIVE_TEXT, PROP_INACTIVE_TEXT, -1 };

static const int Properties_Proprietary[] = { -1 };

/**
 * Returns the list of required, optional, and proprietary properties.
 * Used by ReadPropertyMultiple service.
 *
 * @param pRequired - pointer to list of int terminated by -1, of
 * BACnet required properties for this object.
 * @param pOptional - pointer to list of int terminated by -1, of
 * BACnet optkional properties for this object.
 * @param pProprietary - pointer to list of int terminated by -1, of
 * BACnet proprietary properties for this object.
 */
void Binary_Value_Property_Lists(
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
static struct bv_object_data *Object_List_Element(uint32_t object_instance)
{
    unsigned index;

    while (Binary_Value_Objects_Max == 0) {
        Binary_Value_Init();
    }
    for (index = 0; index < Binary_Value_Objects_Max; index++) {
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
bool Binary_Value_Valid_Instance(uint32_t object_instance)
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
unsigned Binary_Value_Count(void)
{
    return Binary_Value_Objects_Max;
}

/**
 * Determines the object instance-number for a given 0..N index
 * of Multistate Input objects where N is Binary_Value_Count().
 *
 * @param  index - 0..Binary_Value_Count() value
 *
 * @return  object instance-number for the given index
 */
uint32_t Binary_Value_Index_To_Instance(unsigned index)
{
    uint32_t object_instance = UINT32_MAX;

    if (index < Binary_Value_Objects_Max) {
        object_instance = Object_List[index].object_id;
    }

    return object_instance;
}

/**
 * For a given object instance-number, determines a 0..N index
 * of Multistate Input objects where N is Binary_Value_Count().
 *
 * @param  object_instance - object-instance number of the object
 *
 * @return  index for the given instance-number, or Binary_Value_Count()
 * if not valid.
 */
unsigned Binary_Value_Instance_To_Index(uint32_t object_instance)
{
    unsigned index = 0;

    for (index = 0; index < Binary_Value_Objects_Max; index++) {
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
BACNET_BINARY_PV Binary_Value_Present_Value(uint32_t object_instance)
{
    BACNET_BINARY_PV value = BINARY_INACTIVE;
    struct bv_object_data *pObject;

    pObject = Object_List_Element(object_instance);
    if (pObject) {
        if (pObject->value) {
            value = BINARY_ACTIVE;
        }
    }

    return value;
}

/**
 * For a given object instance-number, sets the present-value
 *
 * @param  object_instance - object-instance number of the object
 * @param  value - enumerated binary present-value
 *
 * @return  true if values are within range and present-value is set.
 */
bool Binary_Value_Present_Value_Set(
    uint32_t object_instance, BACNET_BINARY_PV value)
{
    bool status = false;
    struct bv_object_data *pObject;

    pObject = Object_List_Element(object_instance);
    if (pObject) {
        if (!pObject->out_of_service) {
            if (value <= MAX_BINARY_PV) {
                if (value == BINARY_ACTIVE) {
                    pObject->value = true;
                } else if (value == BINARY_INACTIVE) {
                    pObject->value = false;
                }
                status = true;
            }
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
static bool Binary_Value_Present_Value_Write(uint32_t object_instance,
    uint32_t value,
    BACNET_ERROR_CLASS *error_class,
    BACNET_ERROR_CODE *error_code)
{
    bool status = false;
    struct bv_object_data *pObject;

    pObject = Object_List_Element(object_instance);
    if (pObject) {
        if (pObject->writable || pObject->out_of_service) {
            if (value <= MAX_BINARY_PV) {
                if (value == BINARY_ACTIVE) {
                    pObject->value = true;
                } else if (value == BINARY_INACTIVE) {
                    pObject->value = false;
                }
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
bool Binary_Value_Object_Name(
    uint32_t object_instance, BACNET_CHARACTER_STRING *object_name)
{
    bool status = false;
    struct bv_object_data *pObject;

    pObject = Object_List_Element(object_instance);
    if (pObject) {
        status = characterstring_init_ansi(object_name, pObject->object_name);
    }

    return status;
}

/**
 * For a given object instance-number, returns the active text value
 *
 * @param  object_instance - object-instance number of the object
 *
 * @return active text or NULL if not found
 */
char *Binary_Value_Active_Text(uint32_t object_instance)
{
    char *name = NULL;
    struct bv_object_data *pObject;

    pObject = Object_List_Element(object_instance);
    if (pObject) {
        name = (char *)pObject->active_text;
    }

    return name;
}

/**
 * For a given object instance-number, returns the active text value
 *
 * @param  object_instance - object-instance number of the object
 *
 * @return active text or NULL if not found
 */
char *Binary_Value_Inactive_Text(uint32_t object_instance)
{
    char *name = NULL;
    struct bv_object_data *pObject;

    pObject = Object_List_Element(object_instance);
    if (pObject) {
        name = (char *)pObject->inactive_text;
    }

    return name;
}

/**
 * For a given object instance-number, returns the out-of-service
 * property value
 *
 * @param  object_instance - object-instance number of the object
 *
 * @return  out-of-service property value
 */
bool Binary_Value_Out_Of_Service(uint32_t object_instance)
{
    bool value = false;
    struct bv_object_data *pObject;

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
void Binary_Value_Out_Of_Service_Set(uint32_t object_instance, bool value)
{
    struct bv_object_data *pObject;

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
int Binary_Value_Read_Property(BACNET_READ_PROPERTY_DATA *rpdata)
{
    int apdu_len = 0; /* return value */
    BACNET_BIT_STRING bit_string;
    BACNET_CHARACTER_STRING char_string;
    uint32_t present_value = 0;
    uint8_t *apdu = NULL;

    if ((rpdata == NULL) || (rpdata->application_data == NULL)
        || (rpdata->application_data_len == 0)) {
        return 0;
    }
    apdu = rpdata->application_data;
    switch (rpdata->object_property) {
        case PROP_OBJECT_IDENTIFIER:
            apdu_len = encode_application_object_id(
                &apdu[0], OBJECT_BINARY_VALUE, rpdata->object_instance);
            break;
        case PROP_OBJECT_NAME:
            Binary_Value_Object_Name(rpdata->object_instance, &char_string);
            apdu_len
                = encode_application_character_string(&apdu[0], &char_string);
            break;
        case PROP_OBJECT_TYPE:
            apdu_len
                = encode_application_enumerated(&apdu[0], OBJECT_BINARY_VALUE);
            break;
        case PROP_PRESENT_VALUE:
            present_value = Binary_Value_Present_Value(rpdata->object_instance);
            apdu_len = encode_application_enumerated(&apdu[0], present_value);
            break;
        case PROP_STATUS_FLAGS:
            /* note: see the details in the standard on how to use these */
            bitstring_init(&bit_string);
            bitstring_set_bit(&bit_string, STATUS_FLAG_IN_ALARM, false);
            bitstring_set_bit(&bit_string, STATUS_FLAG_FAULT, false);
            bitstring_set_bit(&bit_string, STATUS_FLAG_OVERRIDDEN, false);
            bitstring_set_bit(&bit_string, STATUS_FLAG_OUT_OF_SERVICE,
                Binary_Value_Out_Of_Service(rpdata->object_instance));
            apdu_len = encode_application_bitstring(&apdu[0], &bit_string);
            break;
        case PROP_EVENT_STATE:
            /* note: see the details in the standard on how to use this */
            apdu_len
                = encode_application_enumerated(&apdu[0], EVENT_STATE_NORMAL);
            break;
        case PROP_OUT_OF_SERVICE:
            apdu_len = encode_application_boolean(&apdu[0],
                Binary_Value_Out_Of_Service(rpdata->object_instance));
            break;
        case PROP_ACTIVE_TEXT:
            characterstring_init_ansi(&char_string,
                Binary_Value_Active_Text(rpdata->object_instance));
            apdu_len
                = encode_application_character_string(&apdu[0], &char_string);
            break;
        case PROP_INACTIVE_TEXT:
            characterstring_init_ansi(&char_string,
                Binary_Value_Inactive_Text(rpdata->object_instance));
            apdu_len
                = encode_application_character_string(&apdu[0], &char_string);
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
bool Binary_Value_Write_Property(BACNET_WRITE_PROPERTY_DATA *wp_data)
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
                = WPValidateArgType(&value, BACNET_APPLICATION_TAG_ENUMERATED,
                    &wp_data->error_class, &wp_data->error_code);
            if (status) {
                status = Binary_Value_Present_Value_Write(
                wp_data->object_instance, value.type.Enumerated,
                &wp_data->error_class, &wp_data->error_code);
            }
            break;
        case PROP_OUT_OF_SERVICE:
            status = WPValidateArgType(&value, BACNET_APPLICATION_TAG_BOOLEAN,
                &wp_data->error_class, &wp_data->error_code);
            if (status) {
                Binary_Value_Out_Of_Service_Set(
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
void Binary_Value_Init(void)
{
    unsigned index = 0;

    while (Object_List[index].object_name) {
        index++;
    }
    Binary_Value_Objects_Max = index;
}
