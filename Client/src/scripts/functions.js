const socket = new WebSocket("ws://192.168.64.50:2569");

var content = document.getElementById('content');
var tab;
var table, thead, tbody, tr, td, cell;
var room = ['', 'SN1', 'SN2', 'PHY'];
var histo = ['ROOM', 'BYTE', 'STATUT', 'DATE'];

connexion();

function formRequest(){}

function getAllUsers(){}

function deleteUser(){}

function createUser(){}

function updateUser(){}


socket.onopen = function() 
{
    
    console.log("Client WebSocket: Nouvelle connexion");

};

socket.onclose = function() 
{
    
    console.log("Client WebSocket: Deconnexion");

};

socket.onerror = function(error) 
{
    
    console.error(error);

};

socket.onmessage = function(event) 
{
    const message = event.data.split(';');

    switch (message[0])
    {
        case 'Auth':
            if(message[1] == 1)
            {
                supervision();
                console.log('User connect');
            }
            break;

        case 'State':
            getStateValue(event.data);
            break;

        case 'Histo':
            getHistoValue(event.data);
            break;
            
        default:
            break;

    }
};

function connexion()
{
    var div_form    = document.createElement("div");
    div_form.id     = "div_form";
    div_form.classList.add("div_form");

        var form    = document.createElement("div");
        form.classList.add("form");

            var input_mail              = document.createElement("input");
                input_mail.type         = "mail";
                input_mail.classList.add("input");
                input_mail.value        = "ccauet@la-providence.net";
            form.appendChild(input_mail);

            var input_password          = document.createElement("input");
                input_password.type     = "password";
                input_password.classList.add("input");
                input_password.value    = "vghP71";
            form.appendChild(input_password);

            var input_connexion         = document.createElement("input");
                input_connexion.type    = "button";
                input_connexion.id      = "input_connexion"
                input_connexion.classList.add("input");
                input_connexion.value   = "Connexion";
            form.appendChild(input_connexion);

        div_form.appendChild(form);

    content.appendChild(div_form);

    document.getElementById("input_connexion").
    addEventListener('click', function() 
    {

        var login   = input_mail.value;
        var mdp     = input_password.value;

        data = "Auth"+login+";"+mdp;

        socket.send(data);

    });

}

function disconnection(){}

// Supervision panel
function supervision()
{
    // Remove formulaire connexion
    document.getElementById("div_form").remove();

    // Create elements supervision panel
    var div_supervision     = document.createElement("div");
        div_supervision.id  = "div_supervision"
        div_supervision.classList.add("div_supervision");

        var form    = document.createElement("div");
        form.classList.add("form");

            var input_sensor        = document.createElement("input");
                input_sensor.type   = "button";
                input_sensor.id     = "input_sensor";
                input_sensor.classList.add("input");
                input_sensor.value  = "Sensor State";
            form.appendChild(input_sensor);

            var input_histo         = document.createElement("input");
                input_histo.type    = "button";
                input_histo.id      = "input_histo";
                input_histo.classList.add("input");
                input_histo.value   = "Historical";
            form.appendChild(input_histo);

        div_supervision.appendChild(form);

    content.appendChild(div_supervision);

    // Event click to see sensors state
    document.getElementById("input_sensor").
    addEventListener('click', function()
    {
        getAllSensorState();
    });

    // Event click to see historicals
    document.getElementById("input_histo").
    addEventListener('click', function()
    {
        getAllHisto();
    });
}

function getStateValue(message)
{
    const value = message.split(';');
    tab = value;

    console.log(tab);

    for(j = 0; j < 4; j++)
    {
        tr = document.createElement('tr');
            for(i = 1; i <= 4; i++)
            {
                cellValue(i + j * 4);
                addCellClass(i + j * 4);
            }
        tbody.appendChild(tr);
    }

    cellColor();
}

function getHistoValue(message)
{
    const value = message.split(';');
    tab = value;

    console.log(tab);

    tr = document.createElement('tr');
        for(var i = 1; i < tab.length; i++)
        {
            cellValue(i);
        }
    tbody.appendChild(tr);
}

function cellValue(i)
{
    td = document.createElement('td');
        cell = document.createTextNode(tab[i])
        td.appendChild(cell);
    tr.appendChild(td);
    addCellClass(td, i);
}

function addCellClass(i)
{
    switch (tab[i])
    {
        case 'true':
            td.classList.add("true");
            break;

        case 'false':
            td.classList.add("false");
            break;
            
        default:
            break;

    }
}

function cellColor()
{
    for(var i=0; i<document.getElementsByClassName('false').length; i++)
    {
        document.getElementsByClassName('false')[i].style.color = "#c00000";
        console.log(i);
    }

    for(var i=0; i<document.getElementsByClassName('true').length; i++)
    {
        document.getElementsByClassName('true')[i].style.color = "#00c000";
        console.log(i);
    }
}

function getAllSensorState()
{
    document.getElementById("div_supervision").remove();

    var div_sensor = document.createElement("div");
    div_sensor.classList.add("div_sensor");

        table = document.createElement("table");
        table.classList.add("table_sensor");

            thead = document.createElement('thead');
                tr = document.createElement('tr');
                for(var i=0; i<=3; i++)
                {
                    td = document.createElement('td');
                        cell = document.createTextNode(room[i]);
                        td.appendChild(cell);
                    tr.appendChild(td);
                }
                thead.appendChild(tr);
            table.appendChild(thead);

            tbody = document.createElement('tbody');
                
            table.appendChild(tbody);

        div_sensor.appendChild(table);

    content.appendChild(div_sensor);

    socket.send("State");

}

function getAllHisto()
{
    document.getElementById("div_supervision").remove();

    var div_event = document.createElement("div");
    div_event.classList.add("div_event");

    table = document.createElement("table");
    table.classList.add("table_event");

        thead = document.createElement('thead');
            tr = document.createElement('tr');
            for(var i=0; i<=3; i++)
            {
                td = document.createElement('td');
                    cell = document.createTextNode(histo[i]);
                    td.appendChild(cell);
                tr.appendChild(td);
            }
            thead.appendChild(tr);
        table.appendChild(thead);

        tbody = document.createElement('tbody');
            
        table.appendChild(tbody);

    div_event.appendChild(table);
    
    content.appendChild(div_event);

    socket.send("Histo");

}
