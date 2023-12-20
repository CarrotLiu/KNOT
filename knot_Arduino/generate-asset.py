import gzip

files = [
    ['knot_Arduino/index.html', 'index_page'],
    ['knot_Arduino/style.css', 'style_css'],
    ['knot_Arduino/script.js', 'script_js'],
    ['knot_Arduino/assets/myFavicon.png', 'myFavicon'],
    ['knot_Arduino/mom.html', 'mom_page'],
    ['knot_Arduino/Recording.js', 'recording_js'],
    ['knot_Arduino/lib/p5.sound.min.js', 'p5_sound_js'],
    ['knot_Arduino/lib/p5.js', 'p5_js']
    
]

with open('assets.h', 'w') as out_file:
    for filename, var_name in files:
        with open(filename, 'rb') as in_file:
            data = in_file.read()
            print(f'file: {filename}, {len(data)} bytes')
            data = gzip.compress(data)
            print(f"compressed size: {len(data)} bytes")
            out_file.write(f'static const char {var_name}[] PROGMEM = {{')
            for byte in data:
                out_file.write(hex(byte))
                out_file.write(', ')
            out_file.write('};\n')
