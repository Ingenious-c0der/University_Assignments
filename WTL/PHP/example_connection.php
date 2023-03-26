<html>
<head>

<title>Connecting to Mysql in PHP</title>

<script>


function submitRegister() {
      $.ajax({
           type: "POST",
           url: 'form_submit_handler.php',
           data:{action:'register_event', uname: $('#uname').val(), pword: $('#pword').val},
      });
 }

 function submitDelete() {
      $.ajax({
           type: "POST",
           url: 'form_submit_handler.php',
           data:{action:'delete_event', uname: $('#uname').val()},
      });
 }


</script>

</head>

<body>

<?PHP
$dbhost = 'localhost';
$dbuser = 'root';
$dbpass = 'Snowbell2002$';
$mysqli = new mysqli($dbhost, $dbuser, $dbpass);
if($mysqli->connect_errno > 0){
    die('Unable to connect to database [' . $db->connect_error . ']');
}
echo 'Connected successfully';
$mysqli->select_db("db");
$result  = $mysqli->query("SELECT * FROM tomcat_user_table");
echo '<br>';
echo '<h3>Users in the database</h3>';
while($row = $result->fetch_assoc()){
    echo  $row['username'] . '  -    ' . $row['password'];
    echo '<br>';
}
if(isset($_POST["submit"]))
{
    $username = $_POST["uname"];
    $password = $_POST["pword"];
    $sql = "INSERT INTO tomcat_user_table (username, password) VALUES ('$username', '$password')";
    if($mysqli->query($sql) === true){
        echo "Records added successfully.";
    } else{
        echo "ERROR: Could not able to execute $sql. " . $mysqli->error;
    }
}
?>

<h3>Add user</h3>
<form action="form_submit_handler.php" method="POST">
    <input type = "text" name = "uname" />
    <input type = "text" name = "pword" />
    <input type = "submit" value = "Submit"  />
</form>
<h3>Delete user</h3>
<form action="example_conection.php" method="post">
    <input type = "text" id = "uname" />
    <input type = "submit" value = "Submit" />
</form>

</body>





</html>