
<?php
    header("location: system.php ");
    session_start();
    include "include/functions.php";
    $LoginError = "";
    /*
    if(isset($_POST['submit']))
    {
        $login = $BDD->query("SELECT * FROM `users` WHERE `username` = '".$_POST['username']."' AND `MDP` = '".$_POST['password']."'");
        if($login->rowCount()>0)
        {
            $tab = $login->fetch();

            $_SESSION["Logged"] = true;
            $_SESSION["isAdmin"] = $tab['isAdmin'];
            //réponse a la connection
            header("location: system.php ");

        }
        else{
          $LoginError = "Nom d'utilisateur ou mot de passe incorrect";
        }
    }*/
?>

<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <link rel="stylesheet" href="style/index.css">
  <link rel="stylesheet" href="style/nav.css">
  <link rel="stylesheet" href="style/login_form.css">
  <title>Login</title>
</head>
<body>

<?php 
  include "include/nav.php";
  include "include/login_form.php";
?>
  
</body>
</html>