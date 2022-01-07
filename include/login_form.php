<div class="Login_form">
  <form action="" method="post">
    <img id="login_icon" src="img/login_icon.png" alt="Login_Icon">

    <p><?php echo $LoginError ?></p>
    <input type="text" name="mail" placeholder="Enter your email" required>
    <input type="text" name="password" placeholder="Enter your password" required>

    <input type="submit" name="submit" value="Login">
  </form>
</div>