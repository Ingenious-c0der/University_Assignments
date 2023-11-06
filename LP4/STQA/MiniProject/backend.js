const express = require('express');
const app = express();
const mysql = require('mysql');
const cors = require('cors');
const { user } = require('pg/lib/defaults');
app.use(cors());
app.use(express.urlencoded({ extended: true }));

// parse application/json
app.use(express.json());
// Create a MySQL database connection
const db = mysql.createConnection({
    host: 'localhost',
    user: 'root',
    password: 'Snowbell2002$',
    database: 'stqa_demo',
});

// Connect to the database
db.connect((err) => {
    if (err) {
        console.error('Database connection failed:', err);
        return;
    }
    console.log('Connected to the database');
});

// Express route to add a username to the database
app.post('/addUsername', (req, res) => {
    console.log(req.body); 
    const { username } = req.body;
    console.log(`Adding username "${username}" to the database`);
    // Insert the username into the database
    const query = 'INSERT INTO users (username) VALUES (?)';
    db.query(query, [username], (err, result) => {
        if (err) {
            console.error('Error inserting username:', err);
            res.status(500).send('Error adding username to the database');
        } else {
            console.log('Username added to the database');
            res.status(200).send('Username added to the database');
        }
    });
});
app.get('/getUsernames', (req, res) => {
    // Select all usernames from the database
    console.log('Getting usernames from the database');
    const query = 'SELECT username FROM users';
    db.query(query, (err, result) => {
        if (err) {
            console.error('Error retrieving usernames:', err);
            res.status(500).json({ error: 'Error retrieving usernames from the database' });
        } else {
            const usernames = result.map((row) => row.username);
            res.status(200).json({ usernames });
        }
    });
});

app.delete('/deleteUser/:id', (req, res) => {
    var userId = req.params.id;
    if(userId.includes("Delete")){
        userId = userId.replace("Delete","");
    }
    // Delete the user from the database based on the ID
    const query = 'DELETE FROM users WHERE username = ?';
    db.query(query, [userId], (err, result) => {
        if (err) {
            console.error('Error deleting user:', err);
            res.status(500).send('Error deleting user from the database');
        } else {
            console.log('User deleted from the database');
            res.status(200).send('User deleted from the database');
        }
    });
});


app.listen(3000, () => {
    console.log('Server is running on port 3000');
});