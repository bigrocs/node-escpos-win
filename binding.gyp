{
  "targets": [
    {
      "target_name": "addon",
      "sources": [
      ],
      "cflags!": ["-fno-exceptions"],
      "cflags_cc!": ["-fno-exceptions"],
      "include_dirs": [
        "<!@(node -p \"require('node-addon-api').include\")"
      ],
      'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ],
      'conditions': [
        [
          'OS=="win"',
          {
               'sources': [
                   "srv/binding.cc",
                   "srv/usb.cc",
                   "srv/io.cc"
               ],
               'include_dirs+':
               [
                   # Not needed now
               ]
           }
        ],
      ]
    }
  ]
}
