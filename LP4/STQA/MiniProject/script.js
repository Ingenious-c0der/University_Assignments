document.addEventListener('DOMContentLoaded', () => {
    const nameInput = document.getElementById('nameInput');
    const addButton = document.getElementById('addButton');
    const userList = document.getElementById('userList');

    // Function to add a username to the list
    function addUsername(username) {
        const listItem = document.createElement('li');
        listItem.textContent = username;

        // Create a delete button
        const deleteButton = document.createElement('button');
        deleteButton.textContent = 'Delete';
        deleteButton.className = 'delete-button';

        // Style the delete button
        deleteButton.style.backgroundColor = '#f44336'; // Red background color
        deleteButton.style.color = 'white'; // White text color
        deleteButton.style.border = 'none';
        deleteButton.style.borderRadius = '5px';
        deleteButton.style.padding = '5px 10px';
        deleteButton.style.marginLeft = '10px'; // Add s
        // Append the delete button to the list item
        listItem.appendChild(deleteButton);

        // Attach a click event listener to the delete button
        deleteButton.addEventListener('click', () => {
            // Find the parent <li> element and remove it from the list
            listItem.remove();

            // Extract the username from the <li> element's text content
            const usernameToDelete = listItem.textContent.trim();

            // Send a DELETE request to the server to delete the user
            fetch(`http://localhost:3000/deleteUser/${usernameToDelete}`, {
                method: 'DELETE'
            })
                .then(response => {
                    if (response.ok) {
                        console.log('User deleted from the database.');
                    } else {
                        console.error('Error deleting user from the database.');
                    }
                })
                .catch(error => {
                    console.error('Network error:', error);
                });
        });

        // Append the list item to the user list
        userList.appendChild(listItem);
    }

    // Click event handler for the "Add to List" button
    addButton.addEventListener('click', () => {
        const username = nameInput.value.trim();
        if (username !== '') {
            addUsername(username);

            // Send the username to the server to store in the database
            fetch('http://localhost:3000/addUsername', {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json',
                },
                body: JSON.stringify({ username }),
            })
                .then(response => {
                    if (response.ok) {
                        console.log('Username added to the database.');
                    } else {
                        console.error('Error adding username to the database.');
                    }
                })
                .catch(error => {
                    console.error('Network error:', error);
                });

            nameInput.value = '';
        }
    });

    // Fetch and display usernames from the server on page load
    fetch('http://localhost:3000/getUsernames')
        .then(response => response.json())
        .then(data => {
            data.usernames.forEach(username => {
                addUsername(username);
            });
        })
        .catch(error => {
            console.error('Error fetching usernames from the server:', error);
        });
});