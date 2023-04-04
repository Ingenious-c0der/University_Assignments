function submitForm()
{
    var name = document.getElementById("name").value;
    var pass  = document.getElementById("pass").value;
    if(name == "" || pass == "")
    {
        alert("Please fill all fields...!!!!!!");
    }
    else
    {
        alert("Form Submitted Successfully......");
    }
}