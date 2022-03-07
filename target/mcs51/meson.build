mcs51_ss = ss.source_set()
mcs51_ss.add(files(
  'translate.c',
  'helper.c',
  'cpu.c',
  'gdbstub.c'
))

mcs51_softmmu_ss = ss.source_set()
mcs51_softmmu_ss.add(files('machine.c'))

target_arch += {'mcs51': mcs51_ss}
target_softmmu_arch += {'mcs51': mcs51_softmmu_ss}
