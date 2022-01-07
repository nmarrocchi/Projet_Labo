<?php
    //connexion à la bdd
    try
    {
        $BDD = new PDO('mysql:host=192.168.65.219; dbname=labo; charset=utf8','admin', 'admin');
    }

    catch(Exception $e)
    {
        echo "J'ai eu un problème erreur :".$e->getMessage();
    }


    function check() {
        if($_SESSION && ( $_SESSION["Logged"] == true )) {
            return false;
        } else {
            return true;
        }
    }
?>