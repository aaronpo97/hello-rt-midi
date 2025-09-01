{
  "patcher": {
    "fileversion": 1,
    "appversion": {
      "major": 8,
      "minor": 6,
      "revision": 5,
      "architecture": "x64",
      "modernui": 1
    },
    "classnamespace": "box",
    "rect": [
      200,
      94,
      560,
      346
    ],
    "bglocked": 0,
    "openinpresentation": 0,
    "default_fontsize": 12,
    "default_fontface": 0,
    "gridonopen": 1,
    "gridsize": [
      15,
      15
    ],
    "gridsnaponopen": 1,
    "objectsnaponopen": 1,
    "statusbarvisible": 2,
    "toolbarvisible": 1,
    "lefttoolbarpinned": 0,
    "toptoolbarpinned": 0,
    "righttoolbarpinned": 0,
    "bottomtoolbarpinned": 0,
    "toolbars_unpinned_last_save": 0,
    "tallnewobj": 0,
    "boxanimatetime": 200,
    "enablehscroll": 1,
    "enablevscroll": 1,
    "devicewidth": 0,
    "description": "",
    "digest": "",
    "tags": "",
    "style": "",
    "subpatcher_template": "",
    "assistshowspatchername": 0,
    "boxes": [
      {
        "box": {
          "id": "toggle",
          "maxclass": "toggle",
          "numinlets": 1,
          "numoutlets": 1,
          "outlettype": [
            "int"
          ],
          "parameter_enable": 0,
          "patching_rect": [
            40,
            40,
            24,
            24
          ]
        }
      },
      {
        "box": {
          "id": "metro",
          "maxclass": "newobj",
          "numinlets": 2,
          "numoutlets": 1,
          "outlettype": [
            "bang"
          ],
          "patching_rect": [
            40,
            70,
            69,
            22
          ],
          "text": "metro 2500"
        }
      },
      {
        "box": {
          "id": "counter",
          "maxclass": "newobj",
          "numinlets": 5,
          "numoutlets": 4,
          "outlettype": [
            "int",
            "",
            "",
            "int"
          ],
          "patching_rect": [
            40,
            101,
            100,
            22
          ],
          "text": "counter 60 72"
        }
      },
      {
        "box": {
          "id": "makenote",
          "maxclass": "newobj",
          "numinlets": 3,
          "numoutlets": 2,
          "outlettype": [
            "float",
            "float"
          ],
          "patching_rect": [
            40,
            135,
            115,
            22
          ],
          "text": "makenote 100 1000"
        }
      },
      {
        "box": {
          "id": "noteout",
          "maxclass": "newobj",
          "numinlets": 3,
          "numoutlets": 0,
          "patching_rect": [
            40,
            173,
            60,
            22
          ],
          "text": "noteout"
        }
      }
    ],
    "lines": [
      {
        "patchline": {
          "destination": [
            "makenote",
            0
          ],
          "source": [
            "counter",
            0
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "noteout",
            1
          ],
          "source": [
            "makenote",
            1
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "noteout",
            0
          ],
          "source": [
            "makenote",
            0
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "counter",
            0
          ],
          "source": [
            "metro",
            0
          ]
        }
      },
      {
        "patchline": {
          "destination": [
            "metro",
            0
          ],
          "source": [
            "toggle",
            0
          ]
        }
      }
    ],
    "dependency_cache": [],
    "autosave": 0
  }
}
