                                                                 LESCO Billing System
                                                                      
                                                               Electrically Interstellar
                                                                    
                                                                   Purpose of Project
                                                                        
                                  A console-based software that provides a platform for LESCO employees to 
                                       calculate bills and for customers to view them, respectively.
 
                                                                 Users of the Software

Employees: Working in particular LESCO department

                                                              Functionality for employees

Register a customer and his information / Edit it when required
Reference number | password | Address | Name | Meter type | Initial bill reading |   Due date – 7 days prior at east
Enter current meter reading and view bill of any customer, change bill status 
Enter price of electricity units | Enter the Formula for calculation of electric bill
Set percentage of tax and fixed charges   -   meter rent | TV fees & other charges


Customers: Mainly Households / Businesses

                                                               Functionality for Customers

Accessing bill data by input of unique reference ID & enter their meter reading and view their bill through 3 options:
View previous bill – input required month | View bill as per records of LESCO employees |   View current bill – input current reading  
A Customer can either be Domestic or Commercial and either have a 1 Phase Meter, or a 3 Phase Meter

                                                     Requirements of Software Functionality
Two login options [as employee and as customer]
Set a unique password and username for each employee and customer
Store the username and password in a txt file
Ensure meter type input by both the employee and customer correspond
In case of correct information input - display bill, otherwise show error message
Save the registered bill information in a txt file and employee IDs in another txt file
Generate a password for the customer [e.g. Birthdate]
Employee can change the status of the bill to paid or unpaid
Keep a monthly track of:
Number of unpaid / paid bills |   Amount that is paid or unpaid [All bills] |  Bills  generated for what amount [altogether]
Generate instant bill for the entered meter reading in case the data is not entered by the employee
Display the proper bill on the console including:
Reference number | Address | Name | Current reading | Previous reading | Units consumed | Tax | Additional charges | Total bill | Due date | Status  



                                                               Group Work Division 
                                                                    
                                                                   Usman Faisal
Fulfilling Billing Class requirements: Calculation of each Customer’s bill and associating Bills with Customers according to their respective attributes. Random Generation of date through time functions as well as auto updating of files when any update from the Employee/LESCO is recorded. Creating Billing information file according to given requirements, and setting up the Customer with its billing information. Implementing Inheritance. Updating of Paid / Unpaid Status automatically.

                                                                    Izza Mujeeb
Setting up the customer file according to given requirements, along with saving the input in the Customer Class’s members by loading the file. Bill Calculation of 1  / 3 Phase meters by implementing Polymorphism through virtual functions, setting up New Billing Information in Billing / LESCO classes, also enabling the Employee to View Total Paid and Unpaid Bill Report before or after adding any new Customer. Comment documentation and further establishing ISE Principles in the code.

                                                                     Bisma Ashar
Fulfilling Customer Class Requirements which feature Unique Login System by the Customer, Registration of New Customer, as well as architecting a User-Friendly Interface specially accommodated for the Customer with each Customer’s calculated Bill and Information, and its association with LESCO’s Class. Reading from Tarif Tax File and setting up of Tarif Class information. Requirements Analysis prior to the start of Increment 1 through documentation.

                                                                    Hassan Rehman
Fulfilling requirements of Employee through Unique Login System and File Handling of Employee Data. Setting File content according to requirements initially, establishing read functionality from created file and then associating Employees to LESCO’s main class. Setting up the Employee file, with unique ID and Passwords as well as creation of LESCO’s Employee Billing functionality or reviewing bills of any already registered or newly registered Customer.

