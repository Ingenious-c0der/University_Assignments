const { Builder, By, Key, until } = require('selenium-webdriver');

// Create a new WebDriver instance (replace 'chrome' with your preferred browser)
const driver = new Builder().forBrowser('chrome').build();

async function performUserTest() {
    try {
        // Navigate to your web page
        await driver.get('http://127.0.0.1:5500/LP4/STQA/MiniProject/register.html'); // Update the URL as needed

        // Find the username input field and the "Add to List" button
        await driver.wait(until.elementLocated(By.id('nameInput')), 10000);
        const usernameInput = await driver.findElement(By.id('nameInput'));
        const addButton = await driver.findElement(By.id('addButton'));

        // Enter a username, click the "Add to List" button, and wait for the user to appear in the list
        const newUsername = 'Test user';
        await new Promise(r => setTimeout(r, 3000));
        await usernameInput.sendKeys(newUsername);
        console.log('Textbox Field Passing ✅ ');
        //sleep for 2 seconds 
        await new Promise(r => setTimeout(r, 2000));
        await addButton.click();
        await driver.wait(until.elementLocated(By.xpath(`//ul/li[text()='${newUsername}']`), 10000));
        console.log('Insert DB test Passing ✅ ');
        await new Promise(r => setTimeout(r, 2000));
        // Find the "Delete" button next to the username and click it
        const deleteButton = await driver.findElement(By.xpath(`//ul/li[text()='${newUsername}']//button[@class='delete-button']`));
        
        await deleteButton.click();
        console.log('Delete test Passing ✅ ');
        await new Promise(r => setTimeout(r, 2000));
        // Wait for the username to be removed from the list
        await driver.wait(until.stalenessOf(deleteButton), 10000);
        console.log(' 3/3 tests completed successfully ✅');
    } catch (error) {

        console.error('❌ An error occurred:', error);
    } finally {
        // Quit the WebDriver session
  
        await driver.quit();
    }
}

// Run the user test
performUserTest();