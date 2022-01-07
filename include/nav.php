<div class="nav">
    <?php
      if($_SESSION["Logged"] == true)
      {
        ?>  
          <a href="logout.php"><div class="nav-slot">Déconnexion</div> </a> 
        <?php
          if($_SESSION["isAdmin"] == 1)
          {
            ?>  <a href="admin_panel.php"><div class="nav-slot">Gestion des utilisateurs</div></a>  <?php
          }
      }
      else{
        ?>  <a href="login.php"><div class="nav-slot">Login</div></a>  <?php
      }
    ?>

    <a href="system.php"><div class="nav-slot">Supervisation Labo</div></a>
  </ul>
</div>