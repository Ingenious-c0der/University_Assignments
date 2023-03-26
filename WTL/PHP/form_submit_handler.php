
<?PHP


$dbhost = 'localhost';
$dbuser = 'root';
$dbpass = '';
$mysqli = new mysqli($dbhost, $dbuser, $dbpass);
if($mysqli->connect_errno > 0){
    die('Unable to connect to database [' . $db->connect_error . ']');
}
//print each value in post 
foreach($_POST as $key => $value){
    echo $key . ' = ' . $value . '<br>';
}
$mysqli->select_db("db");
$new_arr = []; 
foreach($_POST as $key => $value){
    echo $key . ' = ' . $value . '<br>';
    array_push($new_arr, $key);
}
if(in_array("delete_name", $new_arr)){
    $delete_name = $_POST['delete_name'];
    $mysqli->query("DELETE FROM tomcat_user_table WHERE username = '$delete_name'");
    echo "Records deleted successfully.";
    die(header("Location: example_connection.php"));
}
else
{
    if(in_array("uname", $new_arr) && in_array("pword", $new_arr)){
        $username = $_POST["uname"];
        $password = $_POST["pword"];
    }
    $mysqli->query("INSERT INTO tomcat_user_table (username, password) VALUES ('$username', '$password')");
    echo "Records added successfully.";
    die(header("Location: example_connection.php"));
}


?>