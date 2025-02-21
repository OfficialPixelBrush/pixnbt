import gzip
player = 'PixelBrushArt'

compress = True

if compress:
    with open(player+'.nbt', 'rb') as f:
        file_content = f.read()
    with gzip.open(player+'.dat', 'wb') as of:
        of.write(file_content)
else:
    with gzip.open(player+'.dat', 'rb') as f:
        file_content = f.read()
    with open(player+'.nbt', 'wb') as of:
        of.write(file_content)