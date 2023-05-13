package com.example.action;

import com.opensymphony.xwork2.ActionSupport;

public class ValidationAction extends ActionSupport {

   private static final long serialVersionUID = 1L;

   private String name;
   private String email;
   private String phone;

   public String execute() {
      // perform validation here
      if (name == null || name.trim().isEmpty()) {
         addFieldError("name", "Name is required");
      }
      if (email == null || email.trim().isEmpty()) {
         addFieldError("email", "Email is required");
      } else if (!email.matches("[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}")) {
         addFieldError("email", "Invalid email address");
      }
      if (phone == null || phone.trim().isEmpty()) {
         addFieldError("phone", "Phone number is required");
      } else if (!phone.matches("\\d{10}")) {
         addFieldError("phone", "Invalid phone number");
      }

      if (hasErrors()) {
         return INPUT;
      } else {
         return SUCCESS;
      }
   }

   public String getName() {
      return name;
   }

   public void setName(String name) {
      this.name = name;
   }

   public String getEmail() {
      return email;
   }

   public void setEmail(String email) {
      this.email = email;
   }

   public String getPhone() {
      return phone;
   }

   public void setPhone(String phone) {
      this.phone = phone;
   }

}