import ClointFusion as cf 
import os 
import time

#opening the excel file in the current directory
excel_path = os.path.join(os.getcwd(),r"excel.xlsx")
cf.launch_any_exe_bat_application(excel_path)

#selecting the column Region for sorting
cf.key_press('right',write_to_window="Excel")
cf.key_press('ctrl','shift','l',write_to_window="Excel")
cf.key_press('alt','down','e',write_to_window="Excel")
cf.key_write_enter("Central")



#applying the header row colours
cf.key_press("f5",write_to_window="Excel")
cf.key_write_enter("A1:G1")
cf.key_press('alt','h',write_to_window="Excel")
cf.key_press('h','right',write_to_window="Excel")
cf.key_hit_enter()
cf.key_press('alt','h')
cf.key_press('f','c')
for i in range(3):
    cf.key_press('shift','right')
for i in range(6):
    cf.key_press('down')
cf.key_press('enter')

#moving to the last column again and sorting it
cf.key_press('ctrl','right',write_to_window="Excel")
cf.key_press('alt','down','s',write_to_window="Excel")

#applying conditional formatting on the last column 
cf.pg.hotkey('ctrl','shiftright','shiftleft','down')
cf.key_press('alt','h','l',write_to_window="Excel")
cf.key_press('s','enter')

# adding black border to the table
cf.key_press('ctrl','a')
cf.key_press('alt','h','b',write_to_window="Excel")
cf.key_press('a')


#saving the excel file changes and copying it to clipboard
cf.key_press("ctrl",'s')
cf.key_press("ctrl",'c',write_to_window="Excel")



#for emailing the excel document
cf.browser_activate("www.gmail.com",dummy_browser = False )

cf.browser_mouse_click_h(User_Visible_Text_Element="Compose")
receiver_emails_ids = "sagarabhyankar.clointfusion@gmail.com avinash.clointfusion@gmail.com"
cf.browser_write_h(Value=receiver_emails_ids)

#to navigate between the fields in email using keyboard
cf.key_press('tab')
cf.key_press('tab')
cf.key_press('tab')

body="Clointfusion task 3 dummy email"
cf.browser_write_h(Value=body)
cf.key_press('tab')
message ="Respected Sir,\nFollowing is dummy Information made by a bot made by Sagar for task 3 of clointfusion.\n Table Data:"

#pasting the copied table into the mail
cf.key_press("ctrl",'v')

#hiting tab to get to attach document and attaching the document
cf.key_press('tab')
cf.key_press('tab')
cf.key_press('tab','enter')

cf.key_write_enter(excel_path)

#waiting for the document to be attached properly
time.sleep(2)

#sending the document
cf.key_press('ctrl','enter')
