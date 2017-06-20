$(document).ready(function() {
    /*
    //var matrix = [0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0];
    var matrix = [0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0];

    var nodes = Math.sqrt(matrix.length);

    var nJson = '{ "nodes": [';

    // parse json nodes
    for (i = 0; i < nodes; i++) {
        nJson += '{ ';
        nJson += '"id": "' + i + '",';
        nJson += '"label": "' + i + '",';
        nJson += '"x": "' + Math.floor((Math.random() * 10)) + '",';
        nJson += '"y": "' + Math.floor((Math.random() * 10)) + '",';
        nJson += '"size": "' + 1 + '"';

        if (i < (nodes - 1)) {
            nJson += '},';
        } else {
            nJson += '}';
        }
    }

    nJson += '], ';

    // parse json edges
    var eJson = ' "edges": [';

    var current = [2];
    var index, nodes, val,
        count = 0,
        x = 0,
        y = 0;

    for (index = 0; index < matrix.length; index++) {

        x = index % nodes;

        val = matrix[index];


        if (val == 1) {
            count++;
            current[0] = x;
            current[1] = y;

            eJson += '{ ';
            eJson += '"id": "' + count + '",';
            eJson += '"source": "' + x + '",';
            eJson += '"target": "' + y + '",';
            eJson += '"type": "' + 'arrow' + '",';
            eJson += '"size": "' + 1 + '"';

            eJson += '},';

        }

        if (x == (nodes - 1)) {
            y++;
        }
    }

    eJson = eJson.slice(0, -1);

    eJson += '] }';

    var all = nJson + eJson;
*/

    $.getJSON("data/data.json", function(data) {

        s = new sigma({
            graph: data,
            renderer: {
                // IMPORTANT:
                // This works only with the canvas renderer, so the
                // renderer type set as "canvas" is necessary here.
                container: 'container'
                    // type: 'canvas'
            },

            settings: {
                defaultNodeColor: '#333',
                defaultLabelColor: '#fff',
                minNodeSize: 20,
                maxNodeSize: 20,
                minEdgeSize: 0.2,
                maxEdgeSize: 3,
                scalingMode: "inside",
                labelSize: "proportional",
                sideMargin: 0.25,
                enableHovering: false,
                mouseWheelEnabled: false
            }
        });

        // Initialize the dragNodes plugin:
        var dragListener = sigma.plugins.dragNodes(s, s.renderers[0]);

        dragListener.bind('startdrag', function(event) {
            console.log(event);
        });

        dragListener.bind('drag', function(event) {
            console.log(event);
        });

        dragListener.bind('drop', function(event) {
            console.log(event);
        });

        dragListener.bind('dragend', function(event) {
            console.log(event);
        });

    });

    /*
        // parse it to json object
        var result = JSON.parse(all);

        s = new sigma({
            graph: result,
            container: 'container',
            settings: {
                defaultNodeColor: '#333',
                defaultLabelColor: '#fff',
                minNodeSize: 20,
                maxNodeSize: 20,
                minEdgeSize: 3,
                maxEdgeSize: 3,
                scalingMode: "inside",
                labelSize: "proportional",
                sideMargin: 0.25,
                enableHovering: false,
                mouseWheelEnabled: false
            }
        });

        sigma.parsers.json(result, {
            container: 'container',
            settings: {
                defaultNodeColor: '#657da3',
                defaultLabelColor: '#ffffff',
                enableHovering: false,
                minNodeSize: 20,
                maxNodeSize: 20,
                minEdgeSize: 3,
                maxEdgeSize: 3,
                scalingMode: "inside",
                defaultLabelSize: "20",
                sideMargin: 0.25
            }
        });

        // Initialize the dragNodes plugin:
        var dragListener = sigma.plugins.dragNodes(s, s.renderers[0]);

        dragListener.bind('startdrag', function(event) {
            console.log(event);
        });

        dragListener.bind('drag', function(event) {
            console.log(event);
        });

        dragListener.bind('drop', function(event) {
            console.log(event);
        });

        dragListener.bind('dragend', function(event) {
            console.log(event);
        });
        */


    $("#showGraph").click(function() {
        $("#showBox").css("display", "block")
        $("#yourGraph").empty();
        $("#properties").empty();

        var data = JSON.parse($("#graphJsonArea").val());


        $.each(data.properties, function(key, val) {
            $('<tr><td>' + key + '</td><td id="' + key + '">' + val + '</td><tr>').appendTo('#properties');
        });


        s = new sigma({
            graph: data.graph,
            renderer: {
                // IMPORTANT:
                // This works only with the canvas renderer, so the
                // renderer type set as "canvas" is necessary here.
                container: 'yourGraph'
                    // type: 'canvas'
            },

            settings: {
                defaultNodeColor: '#333',
                defaultLabelColor: '#fff',
                minNodeSize: 20,
                maxNodeSize: 20,
                minEdgeSize: 0.2,
                maxEdgeSize: 3,
                scalingMode: "inside",
                labelSize: "proportional",
                sideMargin: 0.25,
                enableHovering: false,
                mouseWheelEnabled: false
            }
        });

        // Initialize the dragNodes plugin:
        var dragListener = sigma.plugins.dragNodes(s, s.renderers[0]);

        dragListener.bind('startdrag', function(event) {
            console.log(event);
        });

        dragListener.bind('drag', function(event) {
            console.log(event);
        });

        dragListener.bind('drop', function(event) {
            console.log(event);
        });

        dragListener.bind('dragend', function(event) {
            console.log(event);
        });
    })



})