#include <stdio.h>
#include <stdlib.h>

struct ShopKeeper {
    char name[50];
    double uprice;
    double gst;
    int quantity;
    double gst_amount;
    double price;
    double gprice;
    double finalprice;
};

typedef struct ShopKeeper ShopKeeper;

void calc_dis_price(ShopKeeper* product) {
    if (product->uprice > 500) {
        product->price = product->uprice + product->uprice * 1.0 / 20.0;
    } else {
        product->price = product->uprice;
    }
}

void calc_gst_price(ShopKeeper* product) {
    product->gprice = product->price + product->price * (product->gst / 100.0);
}

void quan_price(ShopKeeper* product) {
    if (product->gprice == 0) {
        product->finalprice = product->quantity * product->price;
    } else {
        product->finalprice = product->quantity * product->gprice;
    }
}

void calc_gst(ShopKeeper* product) {
    product->gst_amount = product->price * (product->gst / 100.0);
}

void print_prod(ShopKeeper* product) {
    printf("Name of the product: %s\n", product->name);
    printf("Unit price of the product: %.2f\n", product->uprice);
    printf("GST applied on the product: %.2f\n", product->gst);
    printf("Quantity of the product: %d\n", product->quantity);
    printf("Price of the product after calculating discount: %.2f\n", product->price);
    printf("Price of the product after applying GST: %.2f\n", product->gprice);
    printf("Final price of the product after applying GST and discount: %.2f\n", product->finalprice);
    printf("-------------------------------------\n\n");
}

int main() {
    ShopKeeper product1 = {"Leather wallet", 1100, 18, 1};
    ShopKeeper product2 = {"Umbrella", 900, 12, 4};
    ShopKeeper product3 = {"Cigarette", 200, 28, 3};
    ShopKeeper product4 = {"Honey", 100, 0, 2};

    ShopKeeper prod[] = {product1, product2, product3, product4};
    int num_products = sizeof(prod) / sizeof(prod[0]);

    for (int i = 0; i < num_products; ++i) {
        calc_dis_price(&prod[i]);
        calc_gst_price(&prod[i]);
        quan_price(&prod[i]);
        calc_gst(&prod[i]);
        print_prod(&prod[i]);
    }

    printf("Q1. Identify the product for which we pay maximum GST?\n");
    printf("Lets calculate the GSTs of all products\n");

    double max_gst = 0;
    char* obj = NULL;
    int j = 1;
    for (int i = 0; i < num_products; ++i) {
        printf("Product%d: %.2f\n", j, prod[i].gst);
        if (prod[i].gst > max_gst) {
            obj = prod[i].name;
            max_gst = prod[i].gst;
        }
        j++;
    }

    printf("The maximum GST among the products is: %.2f\n", max_gst);
    printf("The product for which we pay the max GST amount is %s\n", obj);

    double total_amount = 0;
    printf("\nQ2. Calculate the total amount to be paid to the shopkeeper?\n");

    for (int i = 0; i < num_products; ++i) {
        total_amount += prod[i].finalprice;
    }

    printf("The total amount to be paid to the shopkeeper is: %.2f\n", total_amount);

    return 0;
}
