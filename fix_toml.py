import re
p = r'Resources\Configs\songyuan.toml'
t = open(p, encoding='utf-8').read()
t = t.replace('header_version = 4', '# K90 Pro Max class ABL: with header v4 it loads init_boot\'s generic ramdisk instead of\n# the payload in this image, so the UniXNU payload needs header v0.\nheader_version = 0')
t = t.replace('os_version = "16.0.0"', 'os_version = "16.0.0"')
open(p, 'w', encoding='utf-8', newline='\n').write(t)
print(t)
