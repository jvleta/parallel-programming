#
# For each available platform, determine the
# list of extensions that ARE supported and
# then verify that a particular extension
# is or is not supported.
# 

import shlex
import pyopencl as cl

extension_of_interest = 'cl_khr_icd'

platform_index = -1

platforms = cl.get_platforms()
number_of_platforms = len(platforms)

for i, platform in enumerate(platforms):
    print "Platform %d supports the extensions: %s" % (i, platform.extensions)

    if extension_of_interest in shlex.split(platform.extensions):
        print "Platform %d supports the extension: %s" % (i, extension_of_interest)
    
