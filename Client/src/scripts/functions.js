// Creation WebSocket
const socket = new WebSocket("ws://127.0.0.1:2569");

var content = document.getElementById('content');
var tab, userMail;
// var tableState, tableHisto, thead, tbody, tr, td, cell;

var room = ['', 'SN1', 'SN2', 'PHY'];
var histo = ['ROOM', 'BYTE', 'STATUT', 'DATE'];

connexion();

// Event when the WebSocket is open
socket.onopen = function() 
{  
    console.log("WebSocket: New connexion");
};

// Event when the WebSocket is close
socket.onclose = function() 
{
    console.log("WebSocket: Disconnexion");
};

// Event when the WebSocket had a error
socket.onerror = function(error) 
{
    console.error(error);
};

// Event when the WebSocket receive a message to the server
socket.onmessage = function(event) 
{
    const message = event.data.split(';');

    switch (message[0])
    {
        // Protocol connection
        case 'Auth':
            if(message[1] == 1)
            {
                supervision();
                console.log('User connect');
            }
            else {
                console.log('Error user accompte');
                document.getElementById('LoginError').innerText = "Les identifiants sont incorrects"

            }
            break;

        // Protocol state sensor value    
        case 'State':
            getStateValue(event.data);
            break;

        // Protocol historical Sensor event
        case 'HistoSensor':
            getHistoSensorValue(event.data);
            break;

        // Protocol historical users event
        case 'HistoUsers':
            getHistoUsersValue(event.data);
            break;
            
        default:
            break;

    }
};

// Function user connection 
function connexion()
{
    // Display the connexion form
    var div_form    = document.createElement("div");
    div_form.id     = "div_form";

        var form    = document.createElement("div");
        form.id     = "login_form";

        var LoginError = document.createElement("p");
        LoginError.id = "LoginError";
        form.appendChild(LoginError);

            var input_mail              = document.createElement("input");
                input_mail.type         = "mail";
                input_mail.value        = "ccauet@la-providence.net";
            form.appendChild(input_mail);

            var input_password          = document.createElement("input");
                input_password.type     = "password";
                input_password.value    = "vghP71";
            form.appendChild(input_password);

            var input_connexion         = document.createElement("input");
                input_connexion.type    = "button";
                input_connexion.id      = "input_connexion"
                input_connexion.value   = "Connexion";
            form.appendChild(input_connexion);

        div_form.appendChild(form);

    content.appendChild(div_form);

    // Send the input connection value in the server
    document.getElementById("input_connexion").
    addEventListener('click', function() 
    {
        var login   = input_mail.value;
        var mdp     = input_password.value;

        userMail = login;

        data = "Auth"+login+";"+mdp;

        socket.send(data);
    });

}

function addNavigationMenu(){

    var nav = document.createElement("div");
    nav.id = "nav";

    var nav_ul = document.createElement("ul");
    nav.appendChild(nav_ul);

    // Main menu button
    var input_mainMenu      = document.createElement("li");
    input_mainMenu.id       = "input_mainMenu";
    input_mainMenu.innerText    = "Main menu";

    nav_ul.appendChild(input_mainMenu);

    //input_mainMenu.style.display = "none";

    var nav_li_li   = document.createElement("li");
    nav_ul.appendChild(nav_li_li);

    // Account button
    var input_account        = document.createElement("ul");
    input_account.id     = "input_account";
    input_account.innerText  = userMail;

    nav_li_li.appendChild(input_account);

    // Disconnect button
    var input_disconnect        = document.createElement("li");
    input_disconnect.id     = "input_disconnect";
    input_disconnect.innerText  = "Disconnect ";
    input_disconnect.style.display = "none";
    input_disconnect.onclick = "location.reload()";

    input_account.appendChild(input_disconnect);

    // Disconnect button icon
    var disconnect_exit_icon        = document.createElement("label");
    disconnect_exit_icon.id     = "disconnect_exit_icon";
    disconnect_exit_icon.style.fontFamily = "Material Icons";
    disconnect_exit_icon.innerText = "exit_to_app";

    input_disconnect.appendChild(disconnect_exit_icon);

    document.body.appendChild(nav);
    document.body.insertBefore( nav, document.getElementById( "content" ) );

    // Event click to see SensorState
    document.getElementById("input_account").
    addEventListener('click', function()
    {
        showHideDisconnecInput();
    });


    // Event click to see SensorState
    document.getElementById("input_disconnect").
    addEventListener('click', function()
    {
        location.reload();
    });

}

function showHideDisconnecInput(){

    var input_disconnect = document.getElementById('input_disconnect');
    console.log(input_disconnect.style.display);

    if( input_disconnect.style.display == "none"){
        input_disconnect.style.display = "block";
    }
    else if ( input_disconnect.style.display == "block"){
        input_disconnect.style.display = "none";
    }
}

// Supervision panel
function supervision()
{
    var nav = document.getElementById('nav');

    // Remove formulaire connexion
    document.getElementById("div_form").remove();

    addNavigationMenu();

    document.getElementById( "div_sensor" ).style.display = "block";

    
    // Create elements supervision panel
    var div_supervision     = document.createElement("div");
    div_supervision.id  = "div_supervision"
    div_supervision.classList.add("div_supervision");

    // Histo Button
    var input_histo         = document.createElement("input");
        input_histo.type    = "button";
        input_histo.id      = "input_histo";
        input_histo.classList.add("input");
        input_histo.value   = "Historical";

    content.insertBefore( input_histo, document.getElementById( "div_sensor" ) );

    // Show all sensors state
    getAllSensorState();

    // Sensor Button
    var input_sensor        = document.createElement("input");
        input_sensor.type   = "button";
        input_sensor.id     = "input_sensor";
        input_sensor.classList.add("input");
        input_sensor.value  = "Sensor State";
        input_sensor.style.display = "none";
    
    content.insertBefore( input_sensor, document.getElementById( "div_sensor" ) );

    content.appendChild(div_supervision);
 
    socket.send( "Histo" ); 

    document.getElementById( "div_sensor" ).style.display = "none";
    document.getElementById( "input_sensor" ).style.display = "block";

    // Event click to return to main Menu
    document.getElementById("input_mainMenu").
    addEventListener('click', function()
    {
        document.getElementById('div_sensor').style.display = "none";
        document.getElementById('input_histo').style.display = "block";
        document.getElementById('input_sensor').style.display = "block";
        document.getElementById( "div_event" ).style.display = "none";
        
    });


    // Event click to see Historicals
    document.getElementById("input_histo").
    addEventListener('click', function()
    {
        document.getElementById('div_sensor').style.display = "none";
        document.getElementById('input_histo').style.display = "none";
        document.getElementById('input_sensor').style.display = "block";
        document.getElementById( "div_event" ).style.display = "block";
        document.getElementById( "input_mainMenu" ).style.display = "inline-block";
        
    });

    
    // Event click to see SensorState
    document.getElementById("input_sensor").
    addEventListener('click', function()
    {
        document.getElementById('input_sensor').style.display = "none";
        document.getElementById('input_histo').style.display = "block";
        document.getElementById( "div_sensor" ).style.display = "block";
        document.getElementById( "div_event" ).style.display = "none";
        document.getElementById( "input_mainMenu" ).style.display = "inline-block";
        
    });

}


// Display all sensor state value in table
function getAllSensorState()
{

    let div_sensor = document.createElement("div");
    div_sensor.classList.add("div_sensor");
    div_sensor.id = "div_sensor";

    let table_sensor = document.createElement("table");
    table_sensor.classList.add("table_sensor");
    table_sensor.id = "table_sensor";

    let thead = document.createElement('thead');
    let tr = document.createElement('tr');
    
    for( var i=0; i<=3; i++ ) {
        
        let td   = document.createElement('td')
            , cell = document.createTextNode(room[i]);

        td.appendChild(cell);
        tr.appendChild(td);
    }
    
    thead.appendChild(tr);
    table_sensor.appendChild(thead);

    let tbody = document.createElement('tbody');
            
    table_sensor.appendChild(tbody);
    div_sensor.appendChild(table_sensor);

    content.appendChild(div_sensor);

    // Send value in the server
    socket.send("State");

}

// Get sensor state value 
function getStateValue(message)
{

    const tableBody = document.getElementById( "table_sensor" );
    const value = message.split(';');

    tableBody.innerHTML = "";

    for( j = 0; j < 4; j++ ) {
        const tr = document.createElement( "tr" );
            for( i = 1; i <= 4; i++ )
            {

                const td = document.createElement( "td" )
                const span = document.createElement( "span" )
                span.innerText = value[ i + j * 4 ]
                span.classList.add( `${value[ i + j * 4 ]}` );

                td.appendChild( span )
                tr.appendChild( td )

            }
            tableBody.appendChild(tr);
    }

    /*
    // Send value in the server
    setInterval(
        function () 
        {
            tbody.remove();
            socket.send("State");
            tbody = document.createElement('tbody');
            table.appendChild(tbody);
        }, 1000);
    */
}

// Get historical value
function getHistoSensorValue(message)
{
    let value = message.split( ";" );
    const table = document.getElementById( "table_event_sensor" );

    while( true ) {

        const histoElement = value.slice( 1, 5 );
        value = value.splice( 1, 5 )

        const tr = document.createElement( "tr" )

        for( const elem of histoElement ) {
            const row = document.createElement( "td" );
            row.innerText = elem
            tr.appendChild( row  )
        }
        

        table.appendChild( tr )
        
        if ( value.length )
            break;

    }

}

// Get historical value
function getHistoUsersValue(message)
{
    let value = message.split( ";" );
    const table = document.getElementById( "table_event_users" );

    while( true ) {

        const histoElement = value.slice( 1, 5 );
        value = value.splice( 1, 5 )

        const tr = document.createElement( "tr" )

        for( const elem of histoElement ) {
            const row = document.createElement( "td" );
            row.innerText = elem
            tr.appendChild( row  )
        }
            

        table.appendChild( tr )
        
        if ( value.length )
            break;

    }

}


// Creation cell with value inside
function cellValue( i, value )
{
    let td = document.createElement('td');
    let cell = document.createTextNode(value[i]);
    td.appendChild(cell);
    tr.appendChild(td);
    
    addCellClass(td, i);

}

// Display all user in a table
function getAllUsers(){}

// Delete user in database
function deleteUser(){}

// Add user in database
function createUser(){}

// Modification user in database
function updateUser(){}