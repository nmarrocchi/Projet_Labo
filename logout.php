<?php
    session_start();
    echo "Déconnexion";
    $_SESSION["Logged"] = false;
    session_destroy();
    header("location: index.php ");
?>