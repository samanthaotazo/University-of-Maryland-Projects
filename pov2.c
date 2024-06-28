/*
pov1.c: Create functions to data to linked list and print linked list. Structure of
 type VEHICLE_DETAIL contains additional information like vehicle year and next vehicle
 and can be accessed from the VEHICLE info pointer.
pov2.c: Implement functions for buying and selling vehicles, including adding or
 removing vehicles from the linked list.
 Criteria for vehicle purchase is that vehicle costs less than a vehicle already on the list.
*/

#include<stdio.h>
#include<stdlib.h>
#include "pov.h"
#include <string.h>

const char Color[12][10] = {"Red", "Blue", "White", "Silver", "Orange", "Yellow","Black", "Lime", "Green", "Oliver", "Purple", "Gray"};
const int mileage_range[] = {0, 20000,  50000, 120000};
const float price_range[] = {0, 10000, 40000, 80000};
int transaction_no = 0;
#define MAX_LINE 500

typedef struct vehicle_detail {
    int year; 			//conversion of VIN[9] to an integer year
    MODEL *mp;
    VEHICLE *next_vehicle;			//points to next vehicle
} VEHICLE_DETAIL;
typedef struct valid_vehicle {
    VEHICLE *v;
    void *next;			//points to next vehicle
} VALID_VEHICLE;

MODEL * GetModel(FILE *fp)
{ static MODEL *manu;
    int No_manu = 0;		// number of models in input file fp

    int j;
    char ch;
    MODEL *tmp, *cur;

    tmp = NEW(MODEL);
    if (tmp == NULL) return NULL;

    while(fscanf(fp, "%c", &ch)!= EOF)
    { tmp->code[0] = ch;
        fscanf(fp, "%c%c", &(tmp->code[1]), &(tmp->code[2]));
        // &tmp.code[2] should work as well
        tmp->code[3] = '\0';

        fscanf(fp, "%c", &ch);	// skip the space after code
        j = 0;			// get model name[]
        do
        { fscanf(fp, "%c", &ch);
            tmp->name[j] = ch;
            j++;
        }while(ch!='\n');
        tmp->name[j-1] = '\0';
        tmp->info = NULL;		// last MODEL in the list
        if (No_manu ==0) manu = tmp;	// manu is the head of the list
        else cur->info = tmp;
        cur = tmp;			// stay at the current tail of the list

        No_manu++;
        tmp = NEW(MODEL);
        if (tmp == NULL) return NULL;
    }

    return manu;
}

VEHICLE * GetVehicle (FILE *fp) {
    int i = 0, l, num_of_vehic = 0;
    char tmp_vehic[MAX_LINE];
    VEHICLE *tmp, *cur;
    VEHICLE_DETAIL *tmp_detail, *cur_detail;
    MODEL *tmp_model;

    //header vehicle
    static VEHICLE *all_vehic;
    tmp = NEW(VEHICLE);
    tmp_detail = NEW(VEHICLE_DETAIL);
    tmp->info = tmp_detail;
    //return NULL on error
    if (tmp == NULL) return NULL;

    while (fgets(tmp_vehic, MAX_LINE, fp) != NULL) {
        tmp_model = All_Models;
        tmp->VIN[0] = tmp_vehic[0];
        for (i = 0, l = 0; i < 17; i++, l++) {
            tmp->VIN[i] = tmp_vehic[l];
        }
        tmp->VIN[i] = '\0'; // 17th character is new line
        //add make and model to tmp detail
        while (tmp_model != NULL){
            //if match
            if (tmp_model->code[0] == tmp->VIN[0] && tmp_model->code[1] == tmp->VIN[1] && tmp_model->code[2] == tmp->VIN[2]){
                tmp_detail->mp = (MODEL *)tmp_model;
                break;
            }
            tmp_model = tmp_model->info;
        }

        //get year
        if (tmp->VIN[10] >= 'S' && tmp->VIN[10] <= 'T') {
             tmp_detail->year = tmp->VIN[10] - 'S' + 1995;
        }else if (tmp->VIN[10] >= 'V' && tmp->VIN[10] <= 'Y'){
            tmp_detail->year = tmp->VIN[10] - 'V' + 1997;
        } else if (tmp->VIN[10] >= '1' && tmp->VIN[10] <= '9') {
             tmp_detail->year = tmp->VIN[10] - '1' + 2001;
        } else if (tmp->VIN[10] >= 'A' && tmp->VIN[10] <= 'H') {
             tmp_detail->year = tmp->VIN[10] - 'A' + 2010;
        } else if (tmp->VIN[10] >= 'J' && tmp->VIN[10] <= 'N') {
             tmp_detail->year = tmp->VIN[10] - 'J' + 2018;
        } else if (tmp->VIN[10] == 'P') {
             tmp_detail->year = 2023;
        }else {
             tmp_detail->year = 2025;
        }

        l++; //skip ';'
        for (i = 0; tmp_vehic[l] != ';'; i++, l++){
            tmp->color[i] = tmp_vehic[l];
        }

        tmp->color[i] = '\0';
        l++;    // skip the ; after color
        // get mileage -> intitialize to 0
        tmp->mileage = 0;
        while (tmp_vehic[l] != ';'){
            tmp->mileage = 10*tmp->mileage + (tmp_vehic[l] - '0');
            l++;
        }
        tmp->price = 0;
        l += 2; //skip ; and price sign
        while (tmp_vehic[l] != '.'){
            tmp->price = 10*tmp->price + (tmp_vehic[l] - '0');
            l++;
        }
        //add decimals
        tmp->price = tmp->price + (float)(tmp_vehic[l+1] - '0')/10 + (float)(tmp_vehic[l+2] - '0')/100;

        tmp_detail->next_vehicle = NULL; // last MODEL in the list
        if (num_of_vehic == 0)
            all_vehic = tmp;    // manu is the head of the list
        else {
            cur_detail->next_vehicle = tmp;
        }
        cur = tmp;            // stay at the current tail of the list
        cur_detail = tmp_detail;

        num_of_vehic++;
        tmp = NEW(VEHICLE);
        tmp_detail = NEW(VEHICLE_DETAIL);
        tmp->info = tmp_detail;
        //return null on error
        if (tmp == NULL) return NULL;
    }
    return all_vehic;
}
VALID_VEHICLE *remove_valid (VALID_VEHICLE *tmp, VALID_VEHICLE *follow, VALID_VEHICLE *v_head){
    VALID_VEHICLE *head = v_head;
    //remove vehicle

    return head;
}
void PrintVehicle (VEHICLE *v, FILE *fp) {
    int i;
    VEHICLE *tmp = v;
    VEHICLE_DETAIL *tmp_detail = (VEHICLE_DETAIL *)tmp->info;
    if (v == NULL) {
        printf("error");
    }

    printf("%d ", tmp_detail->year);
    fprintf(fp, "%d ", tmp_detail->year);
    //print color
    for (i = 0; tmp->color[i] != '\0'; i++) {
        fprintf(fp, "%c", tmp->color[i]);
        printf("%c", tmp->color[i]);
    }
    printf(" %s, ", tmp_detail->mp->name);
    fprintf(fp, " %s, ", tmp_detail->mp->name);
    //print mileage
    printf("%d, ", tmp->mileage);
    fprintf(fp, "%d, ", tmp->mileage);
    //print price
    printf("%.2f\n", tmp->price);
    fprintf(fp, "%.2f\n", tmp->price);
}

void PrintAllVehicles (VEHICLE *v, FILE *fp) {
    VEHICLE *tmp = v;
    while(tmp != NULL){
        //print vehicle
        PrintVehicle (tmp, fp);
        tmp = ((VEHICLE_DETAIL *)tmp->info)->next_vehicle;
    }
}

void PrintAllCheaper (VEHICLE *p, FILE *fp, float c) {
    VEHICLE *tmp = p;

    VEHICLE_DETAIL *tmp_detail = (VEHICLE_DETAIL *)tmp->info;
    while(tmp != NULL && tmp->info != NULL){
        //check if price is less than input price
        if (tmp->price < c){
            //print vehicle to screen and file
            PrintVehicle (tmp, fp);
        }
        tmp_detail = (VEHICLE_DETAIL *)tmp->info;
        tmp = tmp_detail->next_vehicle;
    }
}


void PrintAllExpensive (VEHICLE *p, FILE *fp, float c) {
    VEHICLE *tmp = p;
    while(tmp != NULL && tmp->info != NULL){
        //check if price is greater than input price
        if (tmp->price >= c){
            //print vehicle to screen and file
            PrintVehicle (tmp, fp);
        }
        tmp = ((VEHICLE_DETAIL *)(tmp->info))->next_vehicle;
    }
}

void search_and_buy (FILE *fp) {
    int i;
    int SearchKey, userchoice, no_of_valid = 0;
    VEHICLE *tmp;
    VALID_VEHICLE *valid, *valid_follow, *valid_head;

    fprintf(fp, "I am here to buy!\n");
    printf("I am here to buy!\n");
    //make a list of pointers that points to every vehicle
    for (tmp = All_Vehicles; tmp != NULL; tmp = ((VEHICLE_DETAIL *)tmp->info)->next_vehicle){
        valid = NEW(VALID_VEHICLE);
        if (valid == NULL){return;}
        if (no_of_valid == 0){
            valid_head = valid;
        } else {
            valid_follow->next = valid;
        }
        valid->v = tmp;
        valid->next = NULL;
        //move valid_follow to front of list
        valid_follow = valid;
        no_of_valid++;
    }
    //prompt user to choose  make, manufacturer, etc.
    while (1) {
        printf("Enter your search key:\n1. year of made (1995-2024)\n2. color\n3. mileage\n4. price\n");

        scanf("%d", &SearchKey);

        //reset count of number of valid vehicles
        no_of_valid = 0;
        valid = valid_head;
        switch (SearchKey) {
            case 1:
                printf("Enter the year (1995-2024):");
                scanf("%d", &userchoice);
                //traverse valid list only
                while(valid != NULL){
                    if (((VEHICLE_DETAIL *)valid->v->info)->year == userchoice) {
                        PrintVehicle(valid->v, fp);
                        valid_follow = valid;
                        valid = ((VALID_VEHICLE *)valid->next);
                        no_of_valid++;
                    } else {
                        if (valid->v == valid_head->v){
                            valid_head = (VALID_VEHICLE *)valid->next;
                            free(valid);
                            valid = valid_head;
                        } else {
                            valid_follow->next = valid->next;
                            free(valid);
                            valid = (VALID_VEHICLE *)valid_follow->next;
                        }
                    }
                }
                break;
            case 2:
                no_of_valid=0;
                printf("Choose color from ");
                for (i=0; i<12; i++) printf("%2d: %s ", i+1, Color[i]);
                scanf("%d", &userchoice);
                while(valid != NULL) {
                    //if match is found, print out vehicle
                    if (strncmp(Color[userchoice-1], valid->v->color, 10) == 0) {
                        PrintVehicle(valid->v, fp);
                        valid_follow = valid;
                        valid = ((VALID_VEHICLE *)valid->next);
                        no_of_valid++;
                    } else {
                        if (valid->v == valid_head->v){
                            valid_head = (VALID_VEHICLE *)valid->next;
                            free(valid);
                            valid = valid_head;
                        } else {
                            valid_follow->next = valid->next;
                            free(valid);
                            valid = (VALID_VEHICLE *)valid_follow->next;
                        }
                    }
                }
                break;
            case 3:
                printf("Range of the mileage:");
                printf("\n1. %d to %d miles\n2. %d to %d miles\n3. %d to %d miles\n4. %d miles or more\n", mileage_range[0], mileage_range[1] -1, mileage_range[1], mileage_range[2]-1, mileage_range[2], mileage_range[3]-1, mileage_range[3]);
                scanf("%d", &userchoice);
                for (valid = valid_head; valid != NULL;){
                    if (valid->v->mileage >= mileage_range[userchoice-1] && valid->v->mileage < mileage_range[userchoice] && 0 < userchoice < 3){
                        PrintVehicle(valid->v, fp);
                        valid_follow = valid;
                        valid = ((VALID_VEHICLE *)valid->next);
                        no_of_valid++;
                    } else if (valid->v->mileage >= mileage_range[3] && userchoice == 3){
                        PrintVehicle(valid->v, fp);
                        valid_follow = valid;
                        valid = ((VALID_VEHICLE *)valid->next);
                        no_of_valid++;
                    } else {
                        if (valid->v == valid_head->v){
                            valid_head = (VALID_VEHICLE *)valid->next;
                            free(valid);
                            valid = valid_head;
                        } else {
                            valid_follow->next = valid->next;
                            free(valid);
                            valid = (VALID_VEHICLE *)valid_follow->next;
                        }
                    }
                }
                break;
            case 4:
                printf("Range of the price:");
                printf("\n1. $%.2f to $%.2f\n2. $%.2f to $%.2f\n3. $%.2f to $%.2f\n4. $%f or more\n", price_range[0], price_range[1] -1, price_range[1], price_range[2]-1, price_range[2], price_range[3]-1, price_range[3]);
                scanf("%d", &userchoice);
                while (valid != NULL){
                    if (valid->v->price >= price_range[userchoice-1] && valid->v->price < price_range[userchoice] && 0< userchoice < 3){
                        PrintVehicle(valid->v, fp);
                        valid_follow = valid;
                        valid = (VALID_VEHICLE *)valid->next;
                        no_of_valid++;
                    } else if (valid->v->price >= price_range[3] && userchoice == 3){
                        PrintVehicle(valid->v, fp);
                        valid_follow = valid;
                        valid = (VALID_VEHICLE *)valid->next;
                        no_of_valid++;
                    } else {
                        if (valid->v == valid_head->v){
                            valid_head = (VALID_VEHICLE *)valid->next;
                            free(valid);
                            valid = valid_head;
                        } else {
                            valid_follow->next = valid->next;
                            free(valid);
                            valid = (VALID_VEHICLE *)valid_follow->next;
                        }
                    }
                }
                break;
            default:
                printf("Invalid entry.\n");
        }
        if (no_of_valid <= 6) {
            break;
        } else {
            printf("current valid list:\n");
            for (valid = valid_head; valid!= NULL; valid = valid->next){
                printf("\t");
                PrintVehicle(valid->v, fp);
            }
        }
        //if there are 6 or more vehicles, prompt user to narrow their search further
        printf("Narrow down search further by choosing another category.\n");
    }
    //if there are 5 or less, ask if they want to buy
    getchar();
    if (no_of_valid == 0){
        printf("No vehicles matched your query.");
        return;
    }
    printf("Do you want to buy? (Type # (1, 2, 3,...) or 0 for no)\n");
    scanf("%d", &userchoice);
    //check that choice is valid
    if (0 < userchoice <= no_of_valid){
        valid = valid_head;
        //if the user responds yes, update the database and record the transaction in output
        for (i = 1; i < userchoice; i++){
            //traverse list to the selected vehicle
            valid = (VALID_VEHICLE *)valid->next;
        }
        printf("Vehicle sold:\t");
        fprintf(fp, "Transaction %d: %d %s %s sold at $%.2f\n", transaction_no, ((VEHICLE_DETAIL *)valid->v->info)->year, valid->v->color, ((VEHICLE_DETAIL *)valid->v->info)->mp->name, valid->v->price);
        transaction_no++;
        tmp = All_Vehicles;
        VEHICLE *curr = tmp;
        int count;

        while (tmp != NULL){
            if (strncmp(tmp->VIN, valid->v->VIN, 17) == 0){
                //remove vehicle if match
                if (count != 0) {
                    ((VEHICLE_DETAIL *)curr->info)->next_vehicle = ((VEHICLE_DETAIL *) tmp->info)->next_vehicle;
                    free((VEHICLE_DETAIL *)tmp->info);
                    free(tmp);
                } else {
                    All_Vehicles = ((VEHICLE_DETAIL *)tmp->info)->next_vehicle;
                    free((VEHICLE_DETAIL *)tmp->info);
                    free(tmp);
                }
                break;
            }
            count++;
            curr = tmp;
            tmp = ((VEHICLE_DETAIL *)tmp->info)->next_vehicle;
        }
    } else if (userchoice == '0') {
        printf("No purchase made. Have a nice day!");
    } else {
        printf("Invalid response.");
    }
    // return to main menu
    return;
}


void compare_and_sell (FILE *fp) {
    int i;
    char input;
    VEHICLE *tmp;
    fprintf(fp, "I am here to sell!\n");
    printf("I am here to sell!\n");
    VEHICLE *potential = NEW(VEHICLE);
    if (potential == NULL) return;
    //prompt user for data on their vehicle
    printf("Please enter you vehicle's VIN: ");
    i = 0;
    scanf("%c", &potential->VIN[i]);
    for (;i < 18; i++) {
        scanf("%c", &potential->VIN[i]); //no safety check, assuming that user follows directions
    }
    potential->VIN[i] = '\0';
    //printf("VIN: %s", potential->VIN);
    printf("Please enter the color of your vehicle: ");
    i = 0;
    scanf("%c", &input);
    potential->color[i] = input;
    for (i = 1; input != '\n'; i++) {
        scanf("%c", &input); //no safety check, assuming that user follows directions
        potential->color[i] = input;
    }
    potential->color[i-1] = '\0';
    //prompt for mileage
    printf("How many miles does your vehicle have:");
    scanf("%d", &potential->mileage);
    //prompt for price
    printf("What is the price of your vehicle?");
    scanf("%f", &potential->price);
    //loop through vehicle database until you find a vehicle within 5000 miles of the same year and manufacturer at a cheaper price
    for (tmp = All_Vehicles;tmp != NULL; tmp = ((VEHICLE_DETAIL*)tmp->info)->next_vehicle) {
        //if year matches
        if (tmp->VIN[10] == potential->VIN[10]) {
            //check if manufacturer and model are the same
            if ((tmp->VIN[0] == potential->VIN[0]) && (tmp->VIN[1] == potential->VIN[1]) && (tmp->VIN[2] == potential->VIN[2])) {
                //check the mileage
                if (tmp->mileage + 5000 >= potential->mileage && potential->mileage >= tmp->mileage - 5000) {
                    //check that the price is less
                    if (tmp->price > potential->price) {
                        //buy vehicle
                        printf("We will buy the vehicle!");
                        //make a vehicle detail for potential
                        VEHICLE_DETAIL *tmp_detail = NEW(VEHICLE_DETAIL);
                        if (tmp_detail == NULL) { return; }
                        potential->info = tmp_detail;
                        tmp_detail->next_vehicle = All_Vehicles;
                        //fill tmp_detail
                        if (tmp->VIN[10] >= 'S' && tmp->VIN[10] <= 'T') {
                            tmp_detail->year = tmp->VIN[10] - 'S' + 1995;
                        } else if (tmp->VIN[10] >= 'V' && tmp->VIN[10] <= 'Y') {
                            tmp_detail->year = tmp->VIN[10] - 'V' + 1997;
                        } else if (tmp->VIN[10] >= '1' && tmp->VIN[10] <= '9') {
                            tmp_detail->year = tmp->VIN[10] - '1' + 2001;
                        } else if (tmp->VIN[10] >= 'A' && tmp->VIN[10] <= 'H') {
                            tmp_detail->year = tmp->VIN[10] - 'A' + 2010;
                        } else if (tmp->VIN[10] >= 'J' && tmp->VIN[10] <= 'N') {
                            tmp_detail->year = tmp->VIN[10] - 'J' + 2018;
                        } else if (tmp->VIN[10] == 'P') {
                            tmp_detail->year = 2023;
                        } else {
                            tmp_detail->year = 2025;
                        }
                        tmp_detail->next_vehicle = All_Vehicles;
                        MODEL *tmp_model = All_Models;
                        while (tmp_model != NULL) {
                            //if match
                            if (tmp_model->code[0] == tmp->VIN[0] && tmp_model->code[1] == tmp->VIN[1] &&
                                tmp_model->code[2] == tmp->VIN[2]) {
                                tmp_detail->mp = (MODEL *) tmp_model;
                                break;
                            }
                            tmp_model = tmp_model->info;
                        }
                        //set head of linked list to new vehicle
                        All_Vehicles = potential;
                        //print vehicle to file
                        fprintf(fp, "Transaction %d: %d %s %s bought at $%.2f\n", transaction_no, ((VEHICLE_DETAIL *)potential->info)->year, potential->color, ((VEHICLE_DETAIL *)potential->info)->mp->name, potential->price);
                        transaction_no++;
                        //test that vehicle was correctly added to list
                        /*for (tmp = All_Vehicles; tmp != NULL; tmp = ((VEHICLE_DETAIL *)tmp->info)->next_vehicle){
                            PrintVehicle(tmp, fp);
                        }*/
                        return;
                    }
                }
            }
        }
    }
    //otherwise, inform user of decision
    printf("Sorry, we cannot buy your vehicle.\n");
    return;
}