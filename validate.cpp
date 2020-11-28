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
    }


#ifdef __cplusplus
}
#endif