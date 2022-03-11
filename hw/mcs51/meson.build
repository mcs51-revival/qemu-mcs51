mcs51_ss = ss.source_set()
mcs51_ss.add(files('boot.c', 'mcs51.c'))
mcs51_ss.add(when: 'CONFIG_AT89C52', if_true: files('at89c52.c'))
hw_arch += {'mcs51': mcs51_ss}
