import gzip

files = [
    ['knot_Arduino/index.html', 'index_page'],
    ['knot_Arduino/style.css', 'style_css'],
    ['knot_Arduino/script.js', 'script_js'],
    ['knot_Arduino/assets/myFavicon.png', 'myFavicon'],
    ['knot_Arduino/mom.html', 'mom_page'],
    ['knot_Arduino/dad.html', 'dad_page'],
    ['knot_Arduino/jt.html', 'jt_page'],
    ['knot_Arduino/grandma.html', 'grandma_page'],
    ['knot_Arduino/grandpa.html', 'grandpa_page'],
    ['knot_Arduino/Recording.js', 'recording_js']
    
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
