//import { saveAs } from 'file-saver';

var map = new FileReader();
var masset = new FileReader();

MapEditor;


function readMap(e) 
{
	var file = e.target.files[0];
	if (!file) 
	{
		console.warn("Problem while using map file.");
		return;
	}

	map.onload = function(e)
	{
		//var contents = e.target.result;
		//console.log(map);
	};
	map.readAsText(file);
	
	document.getElementById("map_info").innerHTML = file.name;
}

function readMapAssets(e) 
{
	var file = e.target.files[0];
	if (!file) 
	{
		console.warn("Problem while using masset file.");
		return;
	}
	
	masset.onload = function(e)
	{
		//var contents = e.target.result;
		//console.log(masset);
	};
	masset.readAsText(file);
	
	document.getElementById("masset_info").innerHTML = file.name;
}

function checkBoth()
{	 
	if (map.result == null || map.result == "")
	{
		console.warn("Map file is unselected. Please select correct one. (Map filereader is null)");
		return false;
	}
	if (masset.result == null || masset.result == "")
	{
		console.warn("Masset file is unselected. Please select correct one. (Map assets filereader is null)");
		return false;
	}
	
	return true
}

function start()
{
	if (!checkBoth())
		return;
	
	// Hide map selection menu
    document.getElementById("hidden_parent").style.display = 'none';
	
	MapEditor.loadTextures();
	MapEditor.loadMap();
	MapEditor.drawMap();
	MapEditor.updateTiles();
}

function close()
{	
	console.log("Close attempt");
	map.result = null;
	masset.result = null;
	
	MapEditor.close();
	
	// Show selection menu
	document.getElementById("hidden_parent").style.display = 'block';
	
	console.log("Closed");
}

function getMS()
{
	var d = new Date();
	return d.getTime();
}

var MapEditor = 
{
	map : [],
	mapTextures : [],
	
	currentlySelected : -1,
	
	
	changeMapByIndex : function(col, row)
	{
		if (MapEditor.currentlySelected >= 0)
		{
			var ms = getMS();
			
			MapEditor.map[col][row] = MapEditor.currentlySelected;
			
			document.getElementById("i" + col + "_" + row).src = MapEditor.mapTextures[MapEditor.map[col][row]];
			
			console.log("Changed: " + col + " " + row + " to " + MapEditor.currentlySelected + " Operation took: " + + (getMS() - ms) + " ms.");
		}
		else
		{
			console.warn("Please select block you wish to place here.");
		}
	},
	
	changeCurentlySelected : function(newID)
	{
		MapEditor.currentlySelected = newID;
	},
	
	close : function()
	{
		MapEditor.map = [];
		MapEditor.mapTextures = [];
		
		var element = document.getElementById("mapdiv");
		element.innerHTML = "";
	},
	
	loadTextures : async function()
	{
		var ms = getMS();
		
		// Split it by newlines.
		var lines = masset.result.split(/[\r\n]+/g); // tolerate both Windows and Unix linebreaks
		// The loop for each line
		lines.forEach(function(line) 
		{ 
			var i = 0;
			var sc = 0; // , count
			while(true)
			{
				if (i < line.length)
				{
					if (line.charAt(i) == '#')
					{
						// Comment so ignore rest of the line
						break;
					}
					else if (line.charAt(i) == ',')
					{
						sc++;
					}
					else if (sc = 2)
					{
						if (i < line.length)
							MapEditor.mapTextures.push("Assets/Maps/sample_map" + line.slice(i + 13, line.length));
						else
							console.warn("Out of line and comma not found! - Error loading texture.");
						
						break;
					}
				}
			}
		});
		
		console.log("Loaded textures paths in: " + (getMS() - ms) + " ms");
		console.log(MapEditor.mapTextures);
	},
	
	loadMap : async function()
	{
		var ms = getMS();
		var newMap = [];
		
		// Split it by newlines.
		var lines = map.result.split(/[\r\n]+/g); // tolerate both Windows and Unix linebreaks
		// The loop for each line
		lines.forEach(function(line) 
		{ 
			var temp = [];
		
			var i = 0;
			while(i < line.length)
			{
				if (line.charAt(i) != ',' && line.charAt(i) != ' ')
				{
					temp.push(line.charAt(i));
					i += 2;
				}
				else
				{
					i++;
				}
			}
			
			newMap.push(temp);
		});
		
		MapEditor.map = newMap;
		
		console.log("Loaded map in: " + (getMS() - ms) + " ms");
		console.log(MapEditor.map);
	},
	
	drawMap : async function()
	{
		var ms = getMS();
		
		var element = document.getElementById("mapdiv");
		var newMap = "";
		
		for(var i = 0; i < MapEditor.map.length; i++)
		{
			var temp = "";
			
			for(var u = 0; u < MapEditor.map[0].length; u++)
			{
				temp += "<img width='32' height='32' id='i" + i + "_" + u + "' onclick='imgClick(" + i + ", " + u + ")' src='" + MapEditor.mapTextures[MapEditor.map[i][u]] + "'>";
			}
			
			newMap += (temp + "<br />");
		}
		
		element.style.width = MapEditor.map[0].length * 32 + "px";
		element.style.height = MapEditor.map.length * 32 + "px";
		
		element.innerHTML = newMap;
		
		console.log("Drawed map in: " + (getMS() - ms) + " ms");
	},
	
	updateTiles : function()
	{
		var element = document.getElementById("tiles");
		var newTiles = "";
		
		for(var i = 0; i < MapEditor.mapTextures.length; i++)
		{
			newTiles += "<img width='32' height='32' onclick='setSelected(" + i + ")' src='" + MapEditor.mapTextures[i] + "'>";
		}
		
		element.innerHTML = newTiles;
	},
	
	save : function()
	{
		var data = "";
		
		for(var i = 0; i < MapEditor.map.length; i++)
		{
			var temp = "";
			
			for(var u = 0; u < MapEditor.map[0].length; u++)
			{
				if (u == MapEditor.map[0].length - 1) // last
				{
					temp += MapEditor.map[i][u];
				}
				else
				{
					temp += MapEditor.map[i][u] + ', ';
				}
			}
			
			data += (temp + '\n');
		}
		
		console.log(data);
		
		try 
		{
			var isFileSaverSupported = !!new Blob;
			
			//var string = JSON.stringify (data);
			var blob = new Blob([data], {
				type: "text/plain;charset=utf-8"
			});
			
			saveAs(blob, "newMap.map");
		} 
		catch (e) 
		{ 
			console.error("Problem with Blob: "); 
			console.error(e);
		}
	}
};

function imgClick(col, row)
{
	MapEditor.changeMapByIndex(col, row);
}

function setSelected(id)
{
	MapEditor.changeCurentlySelected(id);
}

function save()
{
	if (checkBoth())
	{
		MapEditor.save();
	}
	else
	{
		console.warn("Can't save as there is no data yet. Load files first and edit.");
	}
}

/* Ask before user leave site */
window.onbeforeunload = function (e) 
{
	return 'Are you sure?';
};
