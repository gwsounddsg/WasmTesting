#include <cstdlib>
#include <cstring>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif


    int ValidateValueProvided(const char* value, const char* errorMessage, char* returnErrorMessage) {
        if ((value == NULL) || (value[0] == '\0')) {
            strcpy(returnErrorMessage, errorMessage);
            return 0;
        }

        return 1;
    }


#ifdef __EMSCRIPTEN__
    EMSCRIPTEN_KEEPALIVE
#endif

    int ValidateName(char* name, int maxLength, char* returnErrorMessage) {
        if (ValidateValueProvided(name, "A Product Name must be provided.", returnErrorMessage) == 0) {
            return 0;
        }

        if (strlen(name) > maxLength) {
            strcpy(returnErrorMessage, "The Product Name is too long.");
            return 0;
        }

        return 1;
    }


    int IsCategoryIdInArray(char* selectedCategoryId, int* validCategoryIds, int arrayLength) {
        int categoryId = atoi(selectedCategoryId);

        for (int i=0; i<arrayLength; i++) {
            if (validCategoryIds[i] == categoryId) {
                return 1;
            }
        }

        return 0;
    }


#ifdef __EMSCRIPTEN__
    EMSCRIPTEN_KEEPALIVE
#endif

    int ValidateCategory(char* categoryId, int* validCategoryIds, int arrayLength, char* returnErrorMessage) {
        if (ValidateValueProvided(categoryId, "A Product Category must be selected.", returnErrorMessage) == 0) {
            return 0;
        }

        if (validCategoryIds == NULL || arrayLength == 0) {
            strcpy(returnErrorMessage, "The selected Product Category is not valid.");
            return 0;
        }

        if (IsCategoryIdInArray(categoryId, validCategoryIds, arrayLength) == 0) {
            strcpy(returnErrorMessage, "The selected Product Category is not valid.");
            return 0;
        }

        return 1;
    }


#ifdef __cplusplus
}
#endif