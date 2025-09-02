{
	"patcher" : 	{
		"fileversion" : 1,
		"appversion" : 		{
			"major" : 8,
			"minor" : 6,
			"revision" : 5,
			"architecture" : "x64",
			"modernui" : 1
		}
,
		"classnamespace" : "box",
		"rect" : [ 1199.0, 361.0, 560.0, 320.0 ],
		"bglocked" : 0,
		"openinpresentation" : 0,
		"default_fontsize" : 12.0,
		"default_fontface" : 0,
		"default_fontname" : "Arial",
		"gridonopen" : 1,
		"gridsize" : [ 15.0, 15.0 ],
		"gridsnaponopen" : 1,
		"objectsnaponopen" : 1,
		"statusbarvisible" : 2,
		"toolbarvisible" : 1,
		"lefttoolbarpinned" : 0,
		"toptoolbarpinned" : 0,
		"righttoolbarpinned" : 0,
		"bottomtoolbarpinned" : 0,
		"toolbars_unpinned_last_save" : 0,
		"tallnewobj" : 0,
		"boxanimatetime" : 200,
		"enablehscroll" : 1,
		"enablevscroll" : 1,
		"devicewidth" : 0.0,
		"description" : "",
		"digest" : "",
		"tags" : "",
		"style" : "",
		"subpatcher_template" : "",
		"assistshowspatchername" : 0,
		"boxes" : [ 			{
				"box" : 				{
					"id" : "toggle",
					"maxclass" : "toggle",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "int" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 40.0, 40.0, 24.0, 24.0 ]
				}

			}
, 			{
				"box" : 				{
					"id" : "metro",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "bang" ],
					"patching_rect" : [ 40.0, 70.0, 69.0, 22.0 ],
					"text" : "metro 2000"
				}

			}
, 			{
				"box" : 				{
					"id" : "counter",
					"maxclass" : "newobj",
					"numinlets" : 5,
					"numoutlets" : 4,
					"outlettype" : [ "int", "", "", "int" ],
					"patching_rect" : [ 40.0, 101.0, 100.0, 22.0 ],
					"text" : "counter 60 72"
				}

			}
, 			{
				"box" : 				{
					"id" : "makenote",
					"maxclass" : "newobj",
					"numinlets" : 3,
					"numoutlets" : 2,
					"outlettype" : [ "float", "float" ],
					"patching_rect" : [ 40.0, 135.0, 115.0, 22.0 ],
					"text" : "makenote 100 1000"
				}

			}
, 			{
				"box" : 				{
					"id" : "noteout",
					"maxclass" : "newobj",
					"numinlets" : 3,
					"numoutlets" : 0,
					"patching_rect" : [ 40.0, 173.0, 60.0, 22.0 ],
					"text" : "noteout"
				}

			}
 ],
		"lines" : [ 			{
				"patchline" : 				{
					"destination" : [ "makenote", 0 ],
					"source" : [ "counter", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "noteout", 1 ],
					"source" : [ "makenote", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "noteout", 0 ],
					"source" : [ "makenote", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "counter", 0 ],
					"source" : [ "metro", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "metro", 0 ],
					"source" : [ "toggle", 0 ]
				}

			}
 ],
		"dependency_cache" : [  ],
		"autosave" : 0
	}

}
