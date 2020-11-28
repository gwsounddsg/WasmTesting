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


#ifdef __cplusplus
}
#endif