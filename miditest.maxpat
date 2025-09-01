{
  "patcher": {
    "classnamespace": "box",
    "rect": [
      200,
      120,
      560,
      320
    ],
    "bglocked": 0,
    "openinpresentation": 0,
    "boxes": [
      {
        "box": {
          "id": "toggle",
          "maxclass": "toggle",
          "numinlets": 1,
          "numoutlets": 1,
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
          "text": "metro 250",
          "numinlets": 2,
          "numoutlets": 1,
          "patching_rect": [
            90,
            40,
            70,
            22
          ]
        }
      },
      {
        "box": {
          "id": "counter",
          "maxclass": "newobj",
          "text": "counter 60 72",
          "numinlets": 5,
          "numoutlets": 3,
          "patching_rect": [
            180,
            40,
            100,
            22
          ]
        }
      },
      {
        "box": {
          "id": "makenote",
          "maxclass": "newobj",
          "text": "makenote 100 100",
          "numinlets": 3,
          "numoutlets": 2,
          "patching_rect": [
            300,
            40,
            120,
            22
          ]
        }
      },
      {
        "box": {
          "id": "noteout",
          "maxclass": "newobj",
          "text": "noteout",
          "numinlets": 3,
          "numoutlets": 0,
          "patching_rect": [
            440,
            40,
            60,
            22
          ]
        }
      }
    ],
    "lines": [
      {
        "patchline": {
          "source": [
            "toggle",
            0
          ],
          "destination": [
            "metro",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "metro",
            0
          ],
          "destination": [
            "counter",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "counter",
            0
          ],
          "destination": [
            "makenote",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "makenote",
            0
          ],
          "destination": [
            "noteout",
            0
          ]
        }
      },
      {
        "patchline": {
          "source": [
            "makenote",
            1
          ],
          "destination": [
            "noteout",
            1
          ]
        }
      }
    ]
  }
}
