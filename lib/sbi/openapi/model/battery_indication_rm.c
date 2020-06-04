
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "battery_indication_rm.h"

OpenAPI_battery_indication_rm_t *OpenAPI_battery_indication_rm_create(
    int battery_ind,
    int replaceable_ind,
    int rechargeable_ind
    )
{
    OpenAPI_battery_indication_rm_t *battery_indication_rm_local_var = OpenAPI_malloc(sizeof(OpenAPI_battery_indication_rm_t));
    if (!battery_indication_rm_local_var) {
        return NULL;
    }
    battery_indication_rm_local_var->battery_ind = battery_ind;
    battery_indication_rm_local_var->replaceable_ind = replaceable_ind;
    battery_indication_rm_local_var->rechargeable_ind = rechargeable_ind;

    return battery_indication_rm_local_var;
}

void OpenAPI_battery_indication_rm_free(OpenAPI_battery_indication_rm_t *battery_indication_rm)
{
    if (NULL == battery_indication_rm) {
        return;
    }
    OpenAPI_lnode_t *node;
    ogs_free(battery_indication_rm);
}

cJSON *OpenAPI_battery_indication_rm_convertToJSON(OpenAPI_battery_indication_rm_t *battery_indication_rm)
{
    cJSON *item = NULL;

    if (battery_indication_rm == NULL) {
        ogs_error("OpenAPI_battery_indication_rm_convertToJSON() failed [BatteryIndicationRm]");
        return NULL;
    }

    item = cJSON_CreateObject();
    if (battery_indication_rm->battery_ind >= 0) {
        if (cJSON_AddBoolToObject(item, "batteryInd", battery_indication_rm->battery_ind) == NULL) {
            ogs_error("OpenAPI_battery_indication_rm_convertToJSON() failed [battery_ind]");
            goto end;
        }
    }

    if (battery_indication_rm->replaceable_ind >= 0) {
        if (cJSON_AddBoolToObject(item, "replaceableInd", battery_indication_rm->replaceable_ind) == NULL) {
            ogs_error("OpenAPI_battery_indication_rm_convertToJSON() failed [replaceable_ind]");
            goto end;
        }
    }

    if (battery_indication_rm->rechargeable_ind >= 0) {
        if (cJSON_AddBoolToObject(item, "rechargeableInd", battery_indication_rm->rechargeable_ind) == NULL) {
            ogs_error("OpenAPI_battery_indication_rm_convertToJSON() failed [rechargeable_ind]");
            goto end;
        }
    }

end:
    return item;
}

OpenAPI_battery_indication_rm_t *OpenAPI_battery_indication_rm_parseFromJSON(cJSON *battery_indication_rmJSON)
{
    OpenAPI_battery_indication_rm_t *battery_indication_rm_local_var = NULL;
    cJSON *battery_ind = cJSON_GetObjectItemCaseSensitive(battery_indication_rmJSON, "batteryInd");

    if (battery_ind) {
        if (!cJSON_IsBool(battery_ind)) {
            ogs_error("OpenAPI_battery_indication_rm_parseFromJSON() failed [battery_ind]");
            goto end;
        }
    }

    cJSON *replaceable_ind = cJSON_GetObjectItemCaseSensitive(battery_indication_rmJSON, "replaceableInd");

    if (replaceable_ind) {
        if (!cJSON_IsBool(replaceable_ind)) {
            ogs_error("OpenAPI_battery_indication_rm_parseFromJSON() failed [replaceable_ind]");
            goto end;
        }
    }

    cJSON *rechargeable_ind = cJSON_GetObjectItemCaseSensitive(battery_indication_rmJSON, "rechargeableInd");

    if (rechargeable_ind) {
        if (!cJSON_IsBool(rechargeable_ind)) {
            ogs_error("OpenAPI_battery_indication_rm_parseFromJSON() failed [rechargeable_ind]");
            goto end;
        }
    }

    battery_indication_rm_local_var = OpenAPI_battery_indication_rm_create (
        battery_ind ? battery_ind->valueint : 0,
        replaceable_ind ? replaceable_ind->valueint : 0,
        rechargeable_ind ? rechargeable_ind->valueint : 0
        );

    return battery_indication_rm_local_var;
end:
    return NULL;
}
