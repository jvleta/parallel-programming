import pyopencl as cl

#
# Create a context from devices in first accessible
# platform.
#

platform = cl.get_platforms()[0]
devices = platform.get_devices()
context = cl.create_some_context(devices)
queue = cl.CommandQueue(context)


program_text = open('arith.cl', 'r').read()
program = cl.Program(context, program_text)

try:
    program.build()
except:
    print("Build log:")
    print(program.get_build_info(device, cl.program_build_info.LOG))
    raise

add_kernel = cl.Kernel(program, 'add')
mult_kernel= program.multiply

print("Kernel Name:")
print(mult_kernel.get_info(cl.kernel_info.FUNCTION_NAME))
