var socket = new WebSocket("ws://127.0.0.1:1234");

var inputConnexion = document.getElementById('inputConnexion');

function formRequest(){}

function getCapteursHisto(){}

function getPassagesHisto(){}

function getAllUsers(){}

function deleteUser(){}

function createUser(){}

function updateUser(){}

inputConnexion.addEventListener('click', function() 
{
    
    var login = inputEmail.value;
    var mdp = inputPassword.value;

    data = "Auth"+login+";"+mdp;

    //socket.send(data);

});

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
    
    switch (event.data)
    {

        case 'AuthOk':
            connexion();
            break;
        
        case '':
        
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

function connexion(){}

function disconnection(){}

function systemParameters(){}

function getAllCapteursState(){}

