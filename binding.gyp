{
  "targets": [
    {
      "target_name": "addon",
      "sources": [
        "srv/binding.cc", 
        # "srv/io.cc",
        "srv/usb.cc"
      ],
      "cflags!": ["-fno-exceptions"],
      "cflags_cc!": ["-fno-exceptions"],
      "include_dirs": [
        "<!@(node -p \"require('node-addon-api').include\")"
      ],
      'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ],
    }
  ]
}
