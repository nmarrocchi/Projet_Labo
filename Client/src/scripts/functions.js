// Creation WebSocket
//const socket = new WebSocket("ws://127.0.0.1:2569");
const socket = new WebSocket("ws://192.168.65.31:2569");

var content = document.getElementById('content');
var tab, userMail, index = 0, sensorTabCreated = 0;
let usersIDCard = [], usersMail = [], usersPassword = [], usersIsAdmin = [];

var room = ['', 'SN1', 'SN2', 'PHY'];
var histo = ['ROOM', 'BYTE', 'STATUT', 'DATE'];

connexion();

/* -- Socket Functions -- */

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
                if (message[2] == 1) {
                    supervision();
                }
                else{
                    document.getElementById('LoginError').innerText = "Ce compte ne possède pas les droits d'accès, veuillez contacter un administrateur pour vous connecter";
                }
            }
            else {
                document.getElementById('LoginError').innerText = "Les identifiants sont incorrects"

            }
            break;

        // Protocol state sensor value    
        case 'State':
            if (sensorTabCreated == 0) {
                CreateStateTab(event.data);
            }
            else{
                updateStateTab(event.data);
            }
            
            break;

        // Protocol historical Sensor event
        case 'HistoSystem':
            console.log('passage');
            if(message[1] == "Sensor"){
                getHistoSensorValue(event.data);
            }
            else{
                getHistoPassageValue(event.data);
            }
            break;

        // Select list ID Card  
        case 'getUser':
            SetAllIdCard(event.data);
            break;

        case 'AddHisto':
            if (message[1] == 'Sensor') {
                addHistoSensorValue(event.data);
            }
            else{
                addHistoPassageValue(event.data);
            }
            break;
            
        default:
            break;

    }
};


/* -- WEB Functions -- */

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

// Add nav menu into html
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

// Show / Hide Disconnect Button
function showHideDisconnecInput(){

    var input_disconnect = document.getElementById('input_disconnect');

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
    
    content.insertBefore( input_sensor, document.getElementById( "div_sensor" ) );


    // Show Settings Panel
    systemSettingsPanel();

    // Settings Button
    var input_settings        = document.createElement("input");
    input_settings.type   = "button";
    input_settings.id     = "input_settings";
    input_settings.classList.add("input");
    input_settings.value  = "System Settings";

    content.insertBefore( input_settings, document.getElementById( "div_sensor" ) );

    ManageUserPanel();

    // users Button
    var input_users        = document.createElement("input");
    input_users.type   = "button";
    input_users.id     = "input_users";
    input_users.classList.add("input");
    input_users.value  = "Manage Users";

    content.insertBefore( input_users, document.getElementById( "div_sensor" ) );

    content.appendChild(div_supervision);
 
    socket.send("HistoSystem");

    document.getElementById( "div_sensor" ).style.display = "none";

    // Event click to return to main Menu
    document.getElementById("input_mainMenu").
    addEventListener('click', function()
    {
        document.getElementById( "input_mainMenu" ).style.display = "none";
        document.getElementById('input_histo').style.display = "inline-block";
        document.getElementById('input_sensor').style.display = "inline-block";
        document.getElementById('input_settings').style.display = "inline-block";
        document.getElementById('input_users').style.display = "inline-block";

        document.getElementById( "div_event" ).style.display = "none";
        document.getElementById('div_sensor').style.display = "none";
        document.getElementById('div_settings').style.display = "none";
        document.getElementById('div_users').style.display = "none";
        
    });


    // Event click to see Historicals
    document.getElementById("input_histo").
    addEventListener('click', function()
    {   
        document.getElementById( "input_mainMenu" ).style.display = "inline-block";
        document.getElementById('input_histo').style.display = "none";
        document.getElementById('input_sensor').style.display = "inline-block";
        document.getElementById('input_settings').style.display = "inline-block";
        document.getElementById('input_users').style.display = "inline-block";

        document.getElementById( "div_event" ).style.display = "block";
        document.getElementById('div_sensor').style.display = "none";
        document.getElementById('div_settings').style.display = "none";
        document.getElementById('div_users').style.display = "none";
    });

    
    // Event click to see SensorState
    document.getElementById("input_sensor").
    addEventListener('click', function()
    {
        document.getElementById( "input_mainMenu" ).style.display = "inline-block";
        document.getElementById('input_histo').style.display = "inline-block";
        document.getElementById('input_sensor').style.display = "none";
        document.getElementById('input_settings').style.display = "inline-block";
        document.getElementById('input_users').style.display = "inline-block";

        document.getElementById( "div_event" ).style.display = "none";
        document.getElementById('div_sensor').style.display = "block";
        document.getElementById('div_settings').style.display = "none";
        document.getElementById('div_users').style.display = "none";
    });

    // Event click to system Settings
    document.getElementById("input_settings").
    addEventListener('click', function()
    {
        document.getElementById( "input_mainMenu" ).style.display = "inline-block";
        document.getElementById('input_histo').style.display = "inline-block";
        document.getElementById('input_sensor').style.display = "inline-block";
        document.getElementById('input_settings').style.display = "none";
        document.getElementById('input_users').style.display = "inline-block";

        document.getElementById( "div_event" ).style.display = "none";
        document.getElementById('div_sensor').style.display = "none";
        document.getElementById('div_settings').style.display = "block";
        document.getElementById('div_users').style.display = "none";

        
        AlarmPaneltextColor();
    });

    // Event click to see Manage Users Panel
    document.getElementById("input_users").
    addEventListener('click', function()
    {
        document.getElementById( "input_mainMenu" ).style.display = "inline-block";
        document.getElementById('input_histo').style.display = "inline-block";
        document.getElementById('input_sensor').style.display = "inline-block";
        document.getElementById('input_settings').style.display = "inline-block";
        document.getElementById('input_users').style.display = "none";

        document.getElementById( "div_event" ).style.display = "none";
        document.getElementById('div_sensor').style.display = "none";
        document.getElementById('div_settings').style.display = "none";
        document.getElementById('div_users').style.display = "block";
    });

}


/* -- Actual Sensors Values -- */

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
function CreateStateTab(message)
{

    const tableBody = document.getElementById( "table_sensor" );
    const value = message.split(';');

    let SensorActualState = [];

    tableBody.innerHTML = "";

    for( j = 0; j < 4; j++ ) {
        const tr = document.createElement( "tr" );
            for( i = 1; i <= 4; i++ )
            {
                const td = document.createElement( "td" );
                const span = document.createElement( "span" );
                
                if ((value[i + j * 4] == "true") || (value[i + j * 4] == "false")) {
                    span.className = "SensorStateActualValue";

                    if(SensorActualState[i+j*4] != value[i+j*4]){
                        SensorActualState[i+j*4] = value[i+j*4];
                    }

                    span.id = SensorActualState[i+j*4];
                    span.innerText = SensorActualState[i+j*4];
                }
                else{
                    span.innerText = value[ i + j * 4 ];
                }

                td.appendChild( span );
                tr.appendChild( td );

            }
            tableBody.appendChild(tr);
    }

    sensorTabCreated = 1;
    
    // Send value in the server
    setInterval(
        function () 
        {
            socket.send('State');
        }, 1000);
    
}

// Update sensor Tab values
function updateStateTab(message){
    const newMessage = message.split(';');
    let newSensorvalues = [];
    let spans = document.getElementsByClassName("SensorStateActualValue");

    // Create new tab with receive message but only with true / false state
    for (let i = 0; i < newMessage.length; i++) {
        if ((newMessage[i] == 'true') || (newMessage[i] == 'false')) {
            newSensorvalues.push(newMessage[i]);
        }
    }

    for (let i = 0; i < spans.length; i++) {
        if (spans[i].textContent != newSensorvalues[i]) {
            spans[i].id = newSensorvalues[i];
            spans[i].textContent = newSensorvalues[i];
        }
        
    }

}


/* -- Sensor & Passage Histo -- */

// Insert data in Sensor Histo
function addHistoSensorValue(message){
    const value = message.split(';');
    var SensorHisto = document.getElementById('table_event_sensor');
    var newRow = SensorHisto.insertRow(0);

    for (let i = 0; i < value.length - 2; i++) {
        newRow.insertCell(i).innerText = value[i+2]; 
    }
}

// Insert data in Passage Histo
function addHistoPassageValue(message){
    const value = message.split(';');
    var PassageHisto = document.getElementById('table_event_users');
    var newRow = PassageHisto.insertRow(0);

    for (let i = 0; i < value.length - 2; i++) {
        newRow.insertCell(i).innerText = value[i+2]; 
    }
}

// Get historical value
function getHistoSensorValue(message)
{
    let value = message.split( ";" );
    const table = document.getElementById( "table_event_sensor" );

    while( true ) {

        const histoElement = value.slice( 2, 6 );
        value = value.splice( 2, 6 )

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
function getHistoPassageValue(message)
{
    let value = message.split( ";" );
    const table = document.getElementById( "table_event_users" );

    while( true ) {

        const histoElement = value.slice( 2, 5 );
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


/* -- Manage Users -- */

// CreateManage Users Panel
function ManageUserPanel(){
    var div_users = document.createElement("div");
    div_users.id = "div_users";
    div_users.style.display = "none";


    content.appendChild(div_users);
    form_AddUser(div_users);
    form_ModifyUser(div_users);
    
}

function SetAllIdCard(message){

    let value = message.split( ";" );

    usersIDCard.push(value[1]);
    usersMail.push(value[2]);
    usersPassword.push(value[3]);
    usersIsAdmin.push(value[4]);

    var Modify_idCard = document.createElement("option");
    Modify_idCard.value = value[0]+1;
    Modify_idCard.innerText = value[1]+1;
    Modify_idCard.id = index;
    document.getElementById('Modify_User_idCard').appendChild(Modify_idCard);

    index++;

}

// Create form to add user
function form_AddUser(div_users){
    // Add Form to create new user
    var form_Add_User = document.createElement('form');
    form_Add_User.id = "form_Add_User";

    var title_Add_User = document.createElement("h2");
    title_Add_User.textContent = "Add User";

    var add_User_idCard = document.createElement("input");
    add_User_idCard.type = "text";
    add_User_idCard.id = "add_User_idCard";
    add_User_idCard.placeholder = "ID Card";

    var add_User_mail = document.createElement("input");
    add_User_mail.type = "mail";
    add_User_mail.id = "add_User_mail";
    add_User_mail.placeholder = "Mail la providence";

    var add_User_password = document.createElement("input");
    add_User_password.type = "text";
    add_User_password.id = "add_User_password";
    add_User_password.placeholder = "Mot de passe";

    var add_User_isAdmin = document.createElement("select");
    add_User_isAdmin.id = "add_User_isAdmin";

    var add_User_isAdmin_0 = document.createElement("option");
    add_User_isAdmin_0.value = "0";
    add_User_isAdmin_0.innerText = "No Admin";

    var add_User_isAdmin_1 = document.createElement("option");
    add_User_isAdmin_1.value = "1";
    add_User_isAdmin_1.innerText = "Admin";

    add_User_isAdmin.appendChild(add_User_isAdmin_0);
    add_User_isAdmin.appendChild(add_User_isAdmin_1);

    var add_User_Submit = document.createElement("input");
    add_User_Submit.id = "add_User_Submit";
    add_User_Submit.type = "button";
    add_User_Submit.value = "Add User";
    
    div_users.appendChild(title_Add_User);
    div_users.appendChild(add_User_idCard);
    div_users.appendChild(add_User_mail);
    div_users.appendChild(add_User_password);
    div_users.appendChild(add_User_isAdmin);
    div_users.appendChild(add_User_Submit);

   document.getElementById("add_User_Submit").addEventListener('click', function()
    {
        if ((add_User_idCard.value != "") && (add_User_mail.value != "") && (add_User_password.value != "")) {
            var message = "User;addUser;" + add_User_idCard.value + ";" + add_User_mail.value + ";" + add_User_password.value + ";" + add_User_isAdmin.value;
            socket.send(message)
        } 
    });
}

// Create form to add user
function form_ModifyUser(div_users){
    // Add Form to create new user
    var form_ModifyUser = document.createElement('form');
    form_ModifyUser.id = "form_ModifyUser";

    var title_Modify_User = document.createElement("h2");
    title_Modify_User.textContent = "Modify User";

    div_users.appendChild(title_Modify_User);

    var Modify_User_idCard = document.createElement("select");
    Modify_User_idCard.id = "Modify_User_idCard";
    Modify_User_idCard.placeholder = "ID Card";

    var Modify_idCard_Default = document.createElement("option");
    Modify_idCard_Default.value = "0";
    Modify_idCard_Default.innerText = "ID Card"
    Modify_idCard_Default.id = "0";
    Modify_User_idCard.appendChild(Modify_idCard_Default);

    socket.send("User;getUser");
    
    var Modify_User_mail = document.createElement("input");
    Modify_User_mail.type = "mail";
    Modify_User_mail.id = "Modify_User_mail";
    Modify_User_mail.placeholder = "Mail la providence";

    var Modify_User_password = document.createElement("input");
    Modify_User_password.type = "text";
    Modify_User_password.id = "Modify_User_password";
    Modify_User_password.placeholder = "Mot de passe";

    var Modify_User_isAdmin = document.createElement("select");
    Modify_User_isAdmin.id = "Modify_User_isAdmin";

    var Modify_User_isAdmin_0 = document.createElement("option");
    Modify_User_isAdmin_0.value = "0";
    Modify_User_isAdmin_0.innerText = "No Admin";

    var Modify_User_isAdmin_1 = document.createElement("option");
    Modify_User_isAdmin_1.value = "1";
    Modify_User_isAdmin_1.innerText = "Admin";

    Modify_User_isAdmin.appendChild(Modify_User_isAdmin_0);
    Modify_User_isAdmin.appendChild(Modify_User_isAdmin_1);

    var Modify_User_Submit = document.createElement("input");
    Modify_User_Submit.id = "Modify_User_Submit";
    Modify_User_Submit.type = "button";
    Modify_User_Submit.value = "Modify User";

    var Delete_User_Submit = document.createElement("input");
    Delete_User_Submit.id = "Delete_User_Submit";
    Delete_User_Submit.type = "button";
    Delete_User_Submit.value = "Delete User";
    
    div_users.appendChild(Modify_User_idCard);
    div_users.appendChild(Modify_User_mail);
    div_users.appendChild(Modify_User_password);
    div_users.appendChild(Modify_User_isAdmin);
    div_users.appendChild(Modify_User_Submit);
    div_users.appendChild(Delete_User_Submit);


    // Modify User
    document.getElementById("Modify_User_Submit").
    addEventListener('click', function()
    {
        var test = document.getElementById('Modify_User_idCard').selectedIndex - 1;
        if (test != -1) {
            if((Modify_User_mail.value != "") && (Modify_User_password.value != "")){
                var idCardSelected = document.getElementById('Modify_User_idCard').selectedIndex - 1
                var message = "User;updateUser;" + usersIDCard[idCardSelected] + ";"  + Modify_User_mail.value + ";" + Modify_User_password.value + ";" + Modify_User_isAdmin.selectedIndex;
                socket.send(message);
            }
            
        }
    });

    // Delete User
    document.getElementById("Delete_User_Submit").
    addEventListener('click', function()
    {
        var e = document.getElementById("Modify_User_idCard");
        var result = e.options[e.selectedIndex].id;
        var message = "User;deleteUser;" + usersIDCard[result];
        socket.send(message);
    });

    // Choose different id Card to generate other fields
    document.getElementById("Modify_User_idCard").
    addEventListener('change', function()
    {
        var selectIndex = document.getElementById('Modify_User_idCard').selectedIndex - 1;
        if(selectIndex != -1){
            Modify_User_mail.value = usersMail[selectIndex];
            Modify_User_password.value = usersPassword[selectIndex];
            Modify_User_isAdmin.selectedIndex = selectIndex;
        }
        else{
            Modify_User_mail.value = "";
            Modify_User_password.value = "";
        }

    });
}


/* -- Alarm & Settings Panels -- */

// Set Alarm Panel Buttons Color
function AlarmPaneltextColor(){
    let AlarmPanelButtons = document.getElementsByClassName('AlarmPanelValues');

    for (let i = 0; i < AlarmPanelButtons.length; i++){

        var buttontext = AlarmPanelButtons[i].textContent;
        if ((buttontext == "Active All") || (buttontext == "ON")) {
            AlarmPanelButtons[i].style.color = "green";
        }
        else if ((buttontext == "Desactive All") || (buttontext == "OFF")) {
            AlarmPanelButtons[i].style.color = "red";
        }
    }
}

// System Setting Panel
function systemSettingsPanel(){
    let div_settings = document.createElement("div");
    div_settings.classList.add("div_settings");
    div_settings.id = "div_settings";

    let table_alarm = document.createElement("table");
    table_alarm.classList.add("table_alarm");
    table_alarm.id = "table_alarm";

    let thead = document.createElement('thead');

    table_alarm.appendChild(thead);

    let tbody = document.createElement('tbody');
    
    createAlarmPanel(tbody);
            
    table_alarm.appendChild(tbody);

    div_settings.appendChild(table_alarm);

    content.appendChild(div_settings);

    
    let buttonON = document.getElementsByClassName('SystemButton');
    for (let i = 0; i < buttonON.length; i++) {
        if(buttonON[i].textContent in {"ON" : 1, "Active All" : 1}){
            buttonON[i].style.color = "green";
        }
        else if(buttonON[i].textContent in {"OFF" : 1, "Desactive All" : 1}){
            buttonON[i].style.color = "red";
        }
    }

}

function createAlarmPanel(tableBody){

    let Panel_tr = [ "all", "sn1_siren", "sn1_alarm", "sn2_siren", "sn2_alarm", "sn2_lock", "phy_siren", "phy_alarm"];
    let all_td = ["All Rooms", "ON", "OFF"];
    let sn1_td_1 = ["SN1", "Siren", "ON", "OFF"];
    let sn1_td_2 = ["Alarm", "ON", "OFF"];
    let sn2_td_1 = ["SN2", "Siren", "ON", "OFF"];
    let sn2_td_2 = ["Alarm", "ON", "OFF"];
    let sn2_td_3 = ["Lock", "ON", "OFF"]; 
    let phy_td_1 = ["PHY", "Siren", "ON", "OFF"];
    let phy_td_2 = ["Alarm", "ON", "OFF"];
    
    for (let i = 0; i < Panel_tr.length; i++) {
        var Active_Tr = document.createElement('tr');
        Active_Tr.id = Panel_tr[i];

        switch (i) {
            case 0:
                for (let x = 0; x < all_td.length; x++) {
                    var Active_td = document.createElement('td');
                    Active_td.className = all_td[x];
                    if((Active_td.className == "Active All") || (Active_td.className == "Desactive All") || (Active_td.className == "ON") || (Active_td.className == "OFF")){
                        var activeButton = document.createElement('button');
                        activeButton.className = 'SystemButton';
                        activeButton.value = Active_td.className;
                        activeButton.textContent = activeButton.value;

                        activeButton.addEventListener('click', function()
                        {
                            
                            var message = "Alarm_" + Panel_tr[0] + "_" + this.value;   
                        socket.send(message);
                        });
    
                        Active_td.appendChild(activeButton);
                    }
                    else{
                        Active_td.textContent = all_td[x];
                    }

                    

                    if (x == 0) {
                        Active_td.colSpan = 2;
                    }

                    Active_Tr.appendChild(Active_td);
                }
                break;
        
            case 1:
                for (let x = 0; x < sn1_td_1.length; x++) {
                    var Active_td = document.createElement('td');
                    Active_td.className = sn1_td_1[x];
                    if((Active_td.className == "Active All") || (Active_td.className == "Desactive All") || (Active_td.className == "ON") || (Active_td.className == "OFF")){
                        var activeButton = document.createElement('button');
                        activeButton.className = 'SystemButton';
                        activeButton.value = Active_td.className;
                        activeButton.textContent = activeButton.value;

                        activeButton.addEventListener('click', function()
                        {
                            var message = "Alarm_" + Panel_tr[1] + "_" + this.value;    
                        socket.send(message);
                        });
    
                        Active_td.appendChild(activeButton);
                    }
                    else{
                        Active_td.textContent = sn1_td_1[x];
                    }

                    

                    if (x == 0) {
                        Active_td.rowSpan = 2;
                    }

                    Active_Tr.appendChild(Active_td);
                }
                break;

            case 2:
                for (let x = 0; x < sn1_td_2.length; x++) {
                    var Active_td = document.createElement('td');
                    Active_td.className = sn1_td_2[x];
                    if((Active_td.className == "Active All") || (Active_td.className == "Desactive All") || (Active_td.className == "ON") || (Active_td.className == "OFF")){
                        var activeButton = document.createElement('button');
                        activeButton.className = 'SystemButton';
                        activeButton.value = Active_td.className;
                        activeButton.textContent = activeButton.value;

                        activeButton.addEventListener('click', function()
                        {
                            
                            var message = "Alarm_" + Panel_tr[2] + "_" + this.value;   
                        socket.send(message);
                        });
    
                        Active_td.appendChild(activeButton);
                    }
                    else{
                        Active_td.textContent = sn1_td_2[x];
                    }

                    Active_Tr.appendChild(Active_td);
                }
                break;

            case 3:
                for (let x = 0; x < sn2_td_1.length; x++) {
                    var Active_td = document.createElement('td');
                    Active_td.className = sn2_td_1[x];
                    if((Active_td.className == "Active All") || (Active_td.className == "Desactive All") || (Active_td.className == "ON") || (Active_td.className == "OFF")){
                        var activeButton = document.createElement('button');
                        activeButton.className = 'SystemButton';
                        activeButton.value = Active_td.className;
                        activeButton.textContent = activeButton.value;

                        activeButton.addEventListener('click', function()
                        {
                            
                            var message = "Alarm_" + Panel_tr[3] + "_" + this.value;    
                        socket.send(message);
                        });
    
                        Active_td.appendChild(activeButton);
                    }
                    else{
                        Active_td.textContent = sn2_td_1[x];
                    }

                    

                    if (x == 0) {
                        Active_td.rowSpan = 3;
                    }

                    Active_Tr.appendChild(Active_td);
                }
                break;
                break;
        
            case 4:
                for (let x = 0; x < sn2_td_2.length; x++) {
                    var Active_td = document.createElement('td');
                    Active_td.className = sn2_td_2[x];
                    if((Active_td.className == "Active All") || (Active_td.className == "Desactive All") || (Active_td.className == "ON") || (Active_td.className == "OFF")){
                        var activeButton = document.createElement('button');
                        activeButton.className = 'SystemButton';
                        activeButton.value = Active_td.className;
                        activeButton.textContent = activeButton.value;

                        activeButton.addEventListener('click', function()
                        {
                            
                            var message = "Alarm_" + Panel_tr[4] + "_" + this.value;   
                        socket.send(message);
                        });
    
                        Active_td.appendChild(activeButton);
                    }
                    else{
                        Active_td.textContent = sn2_td_2[x];
                    }

                    Active_Tr.appendChild(Active_td);
                }
                break;
            
            case 5:
                for (let x = 0; x < sn2_td_3.length; x++) {
                    var Active_td = document.createElement('td');
                    Active_td.className = sn2_td_3[x];
                    if((Active_td.className == "Active All") || (Active_td.className == "Desactive All") || (Active_td.className == "ON") || (Active_td.className == "OFF")){
                        var activeButton = document.createElement('button');
                        activeButton.className = 'SystemButton';
                        activeButton.value = Active_td.className;
                        activeButton.textContent = activeButton.value;

                        activeButton.addEventListener('click', function()
                        {
                            
                            var message = "Alarm_" + Panel_tr[5] + "_" + this.value;    
                        socket.send(message);
                        });
    
                        Active_td.appendChild(activeButton);
                    }
                    else{
                        Active_td.textContent = sn2_td_3[x];
                    }

                    Active_Tr.appendChild(Active_td);
                }
                break;
            
            case 6:
                for (let x = 0; x < phy_td_1.length; x++) {
                    var Active_td = document.createElement('td');
                    Active_td.className = phy_td_1[x];
                    if((Active_td.className == "Active All") || (Active_td.className == "Desactive All") || (Active_td.className == "ON") || (Active_td.className == "OFF")){
                        var activeButton = document.createElement('button');
                        activeButton.className = 'SystemButton';
                        activeButton.value = Active_td.className;
                        activeButton.textContent = activeButton.value;

                        activeButton.addEventListener('click', function()
                        {
                            
                            var message = "Alarm_" + Panel_tr[6] + "_" + this.value; 
                        socket.send(message);
                        });
    
                        Active_td.appendChild(activeButton);
                    }
                    else{
                        Active_td.textContent = phy_td_1[x];
                    }

                    

                    if (x == 0) {
                        Active_td.rowSpan = 2;
                    }

                    Active_Tr.appendChild(Active_td);
                }
                break;
            
            case 7:
                for (let x = 0; x < phy_td_2.length; x++) {
                    var Active_td = document.createElement('td');
                    Active_td.className = phy_td_2[x];
                    if((Active_td.className == "Active All") || (Active_td.className == "Desactive All") || (Active_td.className == "ON") || (Active_td.className == "OFF")){
                        var activeButton = document.createElement('button');
                        activeButton.className = 'SystemButton';
                        activeButton.value = Active_td.className;
                        activeButton.textContent = activeButton.value;

                        activeButton.addEventListener('click', function()
                        {
                            
                            var message = "Alarm_" + Panel_tr[7] + "_" + this.value;
                        socket.send(message);
                        });
    
                        Active_td.appendChild(activeButton);
                    }
                    else{
                        Active_td.textContent = phy_td_2[x];
                    }

                    Active_Tr.appendChild(Active_td);
                }
                break;

            default:
                break;        
        }

        

        tableBody.appendChild(Active_Tr);
        
    }
        
}