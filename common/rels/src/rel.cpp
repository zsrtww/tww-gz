extern "C" {
typedef void (*PFN_voidfunc)();
__attribute__((section(".ctors"))) extern PFN_voidfunc _ctors_start[];
__attribute__((section(".ctors"))) extern PFN_voidfunc _ctors_end[];
__attribute__((section(".dtors"))) extern PFN_voidfunc _dtors_start[];
__attribute__((section(".dtors"))) extern PFN_voidfunc _dtors_end[];

void _prolog();
void _epilog();
void _unresolved();
}
namespace twwgz::modules {
extern void main();
extern void exit();
}  // namespace twwgz::modules

void _prolog() {
    // Run global constructors
    for (PFN_voidfunc* ctor = _ctors_start; ctor != _ctors_end && *ctor; ++ctor) {
        (*ctor)();
    }
    // Run main
    twwgz::modules::main();
}

void _epilog() {
    // Run exit
    twwgz::modules::exit();
    // Run global destructors
    for (PFN_voidfunc* dtor = _dtors_start; dtor != _dtors_end && *dtor; ++dtor) {
        (*dtor)();
    }
}

void _unresolved(void) {}

extern "C" void __cxa_pure_virtual() {
    while (1)
        ;
}

namespace std {
void __throw_bad_function_call() {
    while (true)
        ;
}
void __throw_length_error(char const*) {
    while (true)
        ;
}
void __throw_bad_array_new_length() {
    while (true)
        ;
}
void __throw_bad_alloc() {
    while (true)
        ;
}
void __throw_out_of_range(char const*) {
    while (true)
        ;
}
void __throw_domain_error(char const*) {
    while (true)
        ;
}
}  // namespace std