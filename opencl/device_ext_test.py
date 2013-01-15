#
# Determine the resources for each available
# OpenCL device.  
# 

import pyopencl as cl

platforms = cl.get_platforms()

for platform in platforms:
    devices = platform.get_devices()
    for device in devices:
        print "NAME: %s" % device.name
        print "ADDRESS_WIDTH: %d" % device.address_bits
        print "EXTENSIONS: %s" % device.extensions
    
