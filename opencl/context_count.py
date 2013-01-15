import pyopencl as cl

# I'm setting interactive to False because
# I only have 1 platform and 1 device on the
# machine I'm using.

context = cl.create_some_context(interactive=False)

print "Initial Reference count: %u" % context.reference_count

