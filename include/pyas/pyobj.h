
#include <stdint.h>
#include <time.h>

#ifndef _PYOBJ_H_
#define _PYOBJ_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned int pyobj_type ;

struct pyobj_t ;
typedef struct pyobj * pyobj_t ;





 typedef struct {
    int version_pyvm ;
    struct {
        uint32_t arg_count ;
        uint32_t local_count ;
        uint32_t stack_size ;
        uint32_t flags ;
    } header ;
    pyobj_t parent ;
    struct {
        struct {
            uint32_t magic ;
            time_t timestamp ;
            uint32_t source_size ;
        } header ;
        struct {
            pyobj_t interned ;
            pyobj_t bytecode ;
            pyobj_t consts ;
            pyobj_t names ;
            pyobj_t varnames ;
            pyobj_t freevars ;
            pyobj_t cellvars ;
        } content ;
        struct {
            pyobj_t filename ;
            pyobj_t name ;
            uint32_t firstlineno ;
            pyobj_t lnotab ;
        } trailer ;
    } binary ;
 } py_codeblock ;



struct pyobj {

    pyobj_type type ;
    unsigned int refcount ;

    union {
        struct {
            pyobj_t * value ;
            int32_t size ;
        } list ;

        struct {
            char * buffer ;
            int length ;
        } string ;

        py_codeblock * codeblock ;

        union {
            int32_t integer ;
            int64_t integer64 ;
            double real ;
            struct {
                double real ;
                double imag ;
            } complex ;
        } number ;
    } py;
};

#ifdef __cplusplus
}
#endif

#endif /* _PYOBJ_H_ */

