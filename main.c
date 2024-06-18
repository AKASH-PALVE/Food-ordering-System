
/*
Author : Akash Palve
Date : 7 Jube 2024
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// UI DESIGN ---------------------------------------------------------------------------

void showMainMenu() {

    printf("\n\t\t\t\t\t 1. Admin\n");
    printf("\t\t\t\t\t 2. User\n");
    printf("\t\t\t\t\t 3. Exit\n\n");

}

void showAdminMenu() {

    printf("\n\t\t\t\t\t 1. Add Restaurant\n");
    printf("\t\t\t\t\t 2. Remove Restaurant\n");
    printf("\t\t\t\t\t 3. Add Food in Restaurant\n");
    printf("\t\t\t\t\t 4. Remove Food in Restaurant\n");
    printf("\t\t\t\t\t 5. View All Restaurants Available\n");
    printf("\t\t\t\t\t 6. View All Foods Available \n");
    printf("\t\t\t\t\t 7. View All Foods in Restaurant \n");
    printf("\t\t\t\t\t 8. Back\n\n");

}

void showUserMenu() {
    printf("\n\t\t\t\t\t 1. View All Restaurants Available\n");
    printf("\t\t\t\t\t 2. View All Foods Available\n");
    printf("\t\t\t\t\t 3. View All Foods in Restaurant\n");
    printf("\t\t\t\t\t 4. Generate the bill \n");
    printf("\t\t\t\t\t 5. Place The Final Order\n");
    printf("\t\t\t\t\t 6. Back\n\n");
}

// DATA STRUCTURES DESIGN  -------------------------------------------------------- 

typedef struct Food {
    int id;
    char name[50];
    float price;
    struct Food* next;
} Food;

typedef struct Restaurant {
    int id;
    char name[50];
    Food* menu;
    struct Restaurant* next;
} Restaurant;

typedef struct Order {
    int foodId; // unique FoodId
    char foodName[50];
    float foodPrice; 
    int quantity;
    struct Order* next;
} Order;


// Functions -------------------------------------------------------------


Restaurant* findRestaurantById(Restaurant *head,int id){

    Restaurant* temp = head;
    while(temp != NULL){
        if(temp->id == id){
            return temp;
        }
        temp = temp->next;
    }
    return NULL;

}

void addRestaurant(Restaurant **head , int id ,char *name){

    Restaurant* tempx = findRestaurantById(*head,id);
    if(tempx!=NULL){
        printf("Restaurant with id %d already exists\n",id);
        return ;
    }

    Restaurant *newRestaurant = (Restaurant*)malloc(sizeof(Restaurant));

    newRestaurant->id = id;
    strcpy(newRestaurant->name , name);
    newRestaurant->menu = NULL;
    

    Restaurant* temp = *head;

    if(temp == NULL ){
        *head = newRestaurant ;
        newRestaurant->next = NULL ;
      
    }
    else{
        newRestaurant->next = *head;
        *head = newRestaurant ;
    }

    return ;
}

void removeRestaurant(Restaurant** head,int id){

 
   if(*head==NULL){
        printf("No restaurants available\n");
        return ;
   }

    Restaurant* prev = NULL ;
    Restaurant* tmp = *head;

    while(tmp!=NULL && tmp->id != id ){
        prev = tmp ;
        tmp = tmp->next;
    }

    if(tmp==NULL) return ;

    if(tmp->id == id){

        // clear the menu 
        Food* foodNode = tmp->menu;
        while (foodNode != NULL) {
            Food* temp = foodNode;
            foodNode = foodNode->next;
            free(temp);
        }
        
        // head

        if(tmp == *head){
            *head = tmp ->next;
            free(tmp);
            return ;
        } 

        // tail 
        if(tmp->next == NULL){
            prev->next = NULL;
            free(tmp);
            return ;
        }

        prev->next = tmp->next;
        free(tmp);
        return ;

        // general 
    }
 
}

void addFoodInRestaurant(Restaurant* restaurant,int id,char *name,float price){

    // addFoodInRestaurant(findRestaurantById(restaurants, 1), 101, "Pizza", 9.99);
    if(!restaurant)
    {
        printf("!! No Restaurant Found\n");
        return ;
    }

    Food *newFood = (Food*) malloc(sizeof(Food));
    newFood->id = id ;
    strcpy(newFood->name,name);
    newFood->price = price ;

    newFood->next = restaurant->menu ; // restaurant menu acts like the head of the food
    restaurant->menu = newFood ; // updating the new head;

}

void removeFoodInRestaurant(Restaurant* restaurant, int id){

    Food* head = restaurant->menu;


    if(head==NULL){
        printf("No Food available\n");
        return ;
    }

    Food* prev = NULL ;
    Food* tmp = head;

    while(tmp!=NULL && tmp->id != id ){
        prev = tmp ;
        tmp = tmp->next;
    }

    if(tmp==NULL){
        printf("No Food Found with id %d\n",id);
        return ;
    }

    if(tmp->id == id){
        
        // head

        if(tmp == head){
            head = tmp ->next;
            free(tmp);
            return ;
        } 

        // tail 
        if(tmp->next == NULL){
            prev->next = NULL;
            free(tmp);
            return ;
        }

        prev->next = tmp->next;
        free(tmp);
        return ;

        // general 
    }
}



void viewRestaurants(Restaurant *head){

    printf("\n ------------------------------------------------------------------------- \n");
    while (head)
    {
        printf("Restaurant ID: %d ", head->id);
        printf("Restaurant Name: %s\n", head->name);
        head = head->next;        
    }
    
    printf("\n ------------------------------------------------------------------------- \n");

}

void viewAllFoodsInRestaurant(Restaurant *restaurant){
    
    Food *menuHead = restaurant->menu ;
    while(menuHead){
        printf("Food ID: %d   ", menuHead->id);
        printf("Food Name: %s   ", menuHead->name);
        printf("Food Price: %.2f  \n", menuHead->price);
        menuHead = menuHead->next ;
    }
}

void viewAllFoodsAvailable(Restaurant *head){

    printf("\n ------------------------------------------------------------------------- \n");
    while(head){
        viewAllFoodsInRestaurant(head);
        head = head->next ;
    }
    printf("\n ------------------------------------------------------------------------- \n");

}

void placeOrder(){
    printf("\n Please Confirm Placing all the orders in cart \n");
    printf("\nYour Order is Placed Successfully ! \n");
    printf("Please Wait for a little time to get your food delivered ! \n");
    printf("Finally here is the your order \n");
    printf("Enjoy The Food and Visit Again !! \n");

}

void generateBill(Order* head){
   
    float total = 0 ;
    int count = 1 ;
    while(head){
        printf("Sr.No : %d  FoodId : %d FoodName : %s  FoodPrice : %.2f  Quantity : %d \n", count++, head->foodId, head->foodName, head->foodPrice, head->quantity);
        total += (head->foodPrice) * (float)(head->quantity) ;
        head = head->next ;
    }
    printf("Total Bill : %.2f \n", total);

}

Order* CheckOrderAndMakeItReturn(Restaurant* head){
    printf("Do You want to Add item to cart (y/n) : ");
    char ch;
    scanf(" %c", &ch);
    if(ch == 'y'){

        printf("Enter Food Id : ");
        int foodid;
        scanf("%d", &foodid);
        printf("Enter Quantity : ");
        int quantity;
        scanf("%d", &quantity);

        Order* newOrder = (Order*) malloc(sizeof(Order));

        newOrder->foodId = foodid;
        newOrder->quantity = quantity;


        /*----------------------*/

        // pass the food head of all restuants to search ! 

        // char *newname = getFoodNameFromId(foodid,orders);
        // strcpy(newOrder->foodName ,newname );

        Restaurant* temp = head ;
        int f = 0;
        while(temp){
            
            Food* FoodHead = temp->menu;
            while(FoodHead){
                if(FoodHead->id == foodid){
                    strcpy(newOrder->foodName,(FoodHead->name));
                    (newOrder->foodPrice) = (float) (FoodHead->price);
                    f=1;
                    break;
                }
                FoodHead = FoodHead->next;
                if(f==1)
                    break;

            }
            temp = temp ->next ;
        }


      
        
        printf("\nItem added to cart successfully ...\n");
        return newOrder;
    }
    else
        return NULL;
}

void addOrderToCart(Order* orderToAdd,Order** head){ 
    // fn will run after showing the foods menu !.
    // Take foodid and quantity .
    // create new order and put into it acordingly , order is the item of cart !.

    // if order already exist then just update the quantity !
    // else create new order !

    // only add the order arrived ! 

    if(orderToAdd == NULL){
        return ;
    }
    else{
        
        Order* temp = *head;

        if(temp == NULL ){
            *head = orderToAdd ;
            orderToAdd->next = NULL ;
        
        }
        else{
            orderToAdd->next = *head;
            *head = orderToAdd ;
        }

        return ;

    }

}



// Users will navigate through the restaurants avialable and the foods Then they will add the item(foodid order) to cart . 

// Cart Will manage all the orders . Users can remove the order . All is maintained by the food_id. As the foodid is very unique to everyone .

// Generate Bill by looking into cart items (single order of food relaitng to particular foodid) . show the list of items id  , name , quntity .


// Main Function ---------------------------------------------

void main(){
    

    Restaurant *restaurants = NULL ; // nullpointer 
    Food* foods = NULL;
    Order *orders = NULL ; // nullpointer

    // making the resaturant ! 
    
    // pass by address 
    addRestaurant(&restaurants, 1, "Restaurant A"); 
    addRestaurant(&restaurants, 2, "Restaurant B");


    // pass by value
    addFoodInRestaurant(findRestaurantById(restaurants, 1), 101, "Pizza", 9.99);
    addFoodInRestaurant(findRestaurantById(restaurants, 1), 102, "Burger", 4.99);
    addFoodInRestaurant(findRestaurantById(restaurants, 2), 201, "Pasta", 7.99);
    addFoodInRestaurant(findRestaurantById(restaurants, 2), 202, "Salad", 5.49);



    while (1)
    {
        showMainMenu();
        int ch=-1;
        printf("Enter choice : ");
        scanf("%d",&ch);

        if (ch==1)      
        {
            while(1) 
            {

            showAdminMenu();
            int admin_choice=-1;
            printf("Enter choice : ");
            scanf("%d",&admin_choice);
            switch (admin_choice )
            {
            case 1: // 1. Add Restaurant
                printf("Enter Restaurant ID : ");
                int id;
                scanf("%d",&id);
                printf("Enter Restaurant Name : ");
                char name[50];
                scanf("%s",name);
                addRestaurant(&restaurants,id,name);
                break;
            
            case 2: // 2. Remove Restaurant
                printf("Enter Restaurant ID : ");
                int id2;
                scanf("%d",&id2);
                removeRestaurant(&restaurants,id2); // passing ll and id 
                break;
            
            case 3: // 3.Add Food in Restaurant
                printf("Enter Restaurant ID : ");
                int id3;
                scanf("%d",&id3);
                printf("Enter Food ID : ");
                int fid;
                scanf("%d",&fid);
                printf("Enter Food Name : ");
                char fname[50];
                scanf("%s",fname);
                printf("Enter Food Price : ");
                float fprice;
                scanf("%f",&fprice);
                
                addFoodInRestaurant(findRestaurantById(restaurants,id3), fid, fname , fprice);
            
                break;
            
            case 4:// 4. Remove Food in Restaurant

                printf("Enter Restaurant ID : ");
                int id4;
                scanf("%d",&id4);
                printf("Enter Food ID : ");
                int fid2;
                scanf("%d",&fid2);
                removeFoodInRestaurant(findRestaurantById(restaurants,id4), fid2);
                break;

            case 5 : // 5. View All Restaurants Available
                viewRestaurants(restaurants);
                
                break;
            
            case 6: // 6. View All Foods Available
                viewAllFoodsAvailable(restaurants);
                break;
            
            case 7: // 7. View All Foods in Restaurant
                printf("Enter Restaurant ID : ");
                int id5;
                scanf("%d",&id5);
                viewAllFoodsInRestaurant(findRestaurantById(restaurants,id5));
                break;
            
            case 8: // 8. Back
                break;
            
            default:
                printf("Invalid choice\n");
                break;
            }

            if(admin_choice==8)
                break;
            }

        }
        else if(ch==2){

            while(1)
            {

            showUserMenu();
            int user_choice = -1 ;
            printf("Enter choice : ");
            scanf("%d",&user_choice);

            switch (user_choice )
            {
            case 1: // View All Restaurants Available
                viewRestaurants(restaurants); // shows all rs info without the foods 
                break;
            
            case 2: // View All Foods Available
                viewAllFoodsAvailable(restaurants);

                // making order logic ! 
                Order* currOrder = CheckOrderAndMakeItReturn(restaurants);
                if(currOrder){
                    addOrderToCart(currOrder,&orders);
                }
                break;
            
            case 3: // View All Foods Available in a Restaurant
                printf("Enter Restaurant ID : ");
                int id5;
                scanf("%d",&id5);
                printf("\n------------------------------------------------------------------\n");
                viewAllFoodsInRestaurant(findRestaurantById(restaurants,id5));
                printf("\n------------------------------------------------------------------\n");

                // making order logic ! 
                Order* currOrder1 = CheckOrderAndMakeItReturn(restaurants);
                if(currOrder1){
                    addOrderToCart(currOrder1,&orders);
                }

                break;
            
            case 4: // Generate Bill
                generateBill(orders);
                break;    
            
            case 5: // Place Order
                placeOrder();
                break;

            case 6: // Back
                break;    

            default:
                printf("Invalid choice\n");
                break;
            }

            if(user_choice==6)
                break;

            }
        }
        else if(ch == 3 )
            exit(0);
        else{
            printf("Invalid choice\n");
        }
        
    }

}