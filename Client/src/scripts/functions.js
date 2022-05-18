const socket = new WebSocket("ws://192.168.1.110:2569");

var content = document.getElementById('content');
var tab;
var room = ['', 'SN1', 'SN2', 'PHY'];

connexion();

function formRequest(){}

function getCapteursHisto(){}

function getPassagesHisto(){}

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
        case 'AuthOk':
            supervision();
            break;
        case 'val':
            getSensorState(event.data);
            
        default:


    }
    /*if(event.data == "Authtrue" || event.data == "Salttrue"){
        connexion.hidden = true;
        inscription.hidden = true;
        message.hidden = false;
    }else{
        var messageText = document.getElementById('messageText')
        var messageDiv = document.createElement("div");
        var messageContent = event.data;
        messageDiv.innerHTML = "<p>"+messageContent+"</p>";
        messageText.appendChild(messageDiv);
    }*/

};

function connexion()
{
    var div_form            = document.createElement("div");
    div_form.id             = "div_form";
    div_form.classList.add("form");

    var input_mail          = document.createElement("input");
    input_mail.type         = "mail";
    input_mail.classList.add("input");
    input_mail.value        = "ccauet@la-providence.net";

    var input_password      = document.createElement("input");
    input_password.type     = "password";
    input_password.classList.add("input");
    input_password.value    = "vghP71";

    var input_connexion     = document.createElement("input");
    input_connexion.type    = "submit";
    input_connexion.id      = "input_connexion"
    input_connexion.classList.add("input");
    input_connexion.value   = "Connexion";

    div_form.appendChild(input_mail);
    div_form.appendChild(input_password);
    div_form.appendChild(input_connexion);

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

function supervision()
{
    document.getElementById("div_form").remove();

    var div_supervision     = document.createElement("div");
        div_supervision.id  = "div_supervision"
        div_supervision.classList.add("div_supervision");

    var input_sensor        = document.createElement("input");
        input_sensor.type   = "submit";
        input_sensor.id     = "input_sensor";
        input_sensor.classList.add("input");
        input_sensor.value  = "Sensor State";

    var input_histo         = document.createElement("input");
        input_histo.type    = "submit";
        input_histo.id      = "input_histo";
        input_histo.classList.add("input");
        input_histo.value   = "Histo";

    div_supervision.appendChild(input_sensor);
    div_supervision.appendChild(input_histo);

    content.appendChild(div_supervision);

    document.getElementById("input_sensor").
    addEventListener('click', function()
    {
        getAllSensorState();
    });

    document.getElementById("input_histo").
    addEventListener('click', function()
    {
        getAllHisto();
    });
}

function getSensorState(message)
{
    const value = message.split(';');
    console.log(value);
    tab = value;
}

function addCellClass(td, i)
{
    if(tab[i] == "true")
    {
        td.classList.add("true");
    }
    else
    {
        td.classList.add("false");
    }
}

function cellValue(tr, i)
{
    var td = document.createElement('td');
        var cell = document.createTextNode(tab[i])
        td.appendChild(cell);
    tr.appendChild(td);
    addCellClass(td, i);
}

function cellColor()
{
    for(var i=0; i<document.getElementsByClassName('false').length; i++)
    {
        document.getElementsByClassName('false')[i].style.color = "#ff0000";
        console.log(i);
    }

    for(var i=0; i<document.getElementsByClassName('true').length; i++)
    {
        document.getElementsByClassName('true')[i].style.color = "#00ff00";
        console.log(i);
    }
}

function getAllSensorState()
{
    document.getElementById("div_supervision").remove();

    var div_sensor = document.createElement("div");

    var table_sensor = document.createElement("table");

        var thead = document.createElement('thead');
            var tr = document.createElement('tr');
            for(var i=0; i<=3; i++)
            {
                var td = document.createElement('td');
                    var cell = document.createTextNode(room[i]);
                    td.appendChild(cell);
                tr.appendChild(td);
            }
            thead.appendChild(tr);
        table_sensor.appendChild(thead);

        var tbody = document.createElement('tbody');
            var tr = document.createElement('tr');
                var td = document.createElement('td');
                    var cell = document.createTextNode('Continuity');
                    td.appendChild(cell);
                tr.appendChild(td)
                for(var i=1; i<=3; i++)
                {
                    cellValue(tr, i);
                }
            tbody.appendChild(tr);
            var tr = document.createElement('tr');
                var td = document.createElement('td');
                    var cell = document.createTextNode('Sensor');
                    td.appendChild(cell);
                tr.appendChild(td)
                for(var i=4; i<=6; i++)
                {
                    cellValue(tr, i);
                }
            tbody.appendChild(tr);
            var tr = document.createElement('tr');
                var td = document.createElement('td');
                    var cell = document.createTextNode('Tamper');
                    td.appendChild(cell);
                tr.appendChild(td);
                for(var i=7; i<=9; i++)
                {
                    cellValue(tr, i);
                }
            tbody.appendChild(tr);
            var tr = document.createElement('tr');
                var td = document.createElement('td');
                    var cell = document.createTextNode('Presence');
                    td.appendChild(cell);
                tr.appendChild(td);
                for(var i=10; i<=12; i++)
                {
                    cellValue(tr, i);
                }
                tbody.appendChild(tr);
        table_sensor.appendChild(tbody);

    div_sensor.appendChild(table_sensor);

    content.appendChild(div_sensor);

    cellColor();
}

function getAllHisto()
{
    var div_event = document.createElement("div");

    var table_event = document.createElement("table");
        var thead = document.createElement('thead');
            var tr = document.createElement('tr');
            for(var i=0; i<=3; i++)
            {
                var td = document.createElement('td');
                td.value = i;
                tr.appendChild(td)
            }
            thead.appendChild(tr);
        var tbody = document.createElement('tbody');
        for(var i=0; i<=2; i++)
        {
            var tr = document.createElement('tr');
            for(var j=0; j<=3; j++)
            {
                var td = document.createElement('td');
                    var cell = document.createTextNode(j + i);
                    td.appendChild(cell);
                tr.appendChild(td)
            }
            tbody.appendChild(tr);
        }
        table_event.appendChild(tbody);
    div_event.appendChild(table_event);
    
    content.appendChild(div_event);
}
