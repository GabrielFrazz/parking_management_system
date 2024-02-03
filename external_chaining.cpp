#include "external_chaining.h"

int hash(int cod, int size)
{
    return cod % size;
}

void creates_hash(const char *hash_name, int size)
{
    FILE *hash_file = fopen(hash_name, "wb");
    if (hash_file == NULL)
    {
        printf("Error creating hash file\n");
        return;
    }
    for (int i = 0; i < size; i++)
    {
        HashCompartment *compartment = (HashCompartment *)malloc(sizeof(HashCompartment));
        compartment = hash_compartment(-1);
        saves_compartment(compartment, hash_file);

        free(compartment);
    }
    fclose(hash_file);
}

int search(int cod, FILE *hash_file, const char *data_file_name, int size)
{
    int h = hash(cod, size);
    int hash_position = h * sizeof(int);

    if(hash_position == 0){
        rewind(hash_file);
    }else{
        fseek(hash_file, hash_position, SEEK_SET);
    }

    HashCompartment *compartment = reads_compartment(hash_file);

    if(compartment->next == -1){
        return -1;
    }else{
        FILE *data_file = fopen(data_file_name, "rb");

        if(data_file == NULL){
            printf("Error opening data file\n");
            return -1;
        }

        if(compartment->next == 0){
            rewind(data_file);
        }else{
            fseek(data_file, customerSize() * compartment->next, SEEK_SET);
        }

        int position = compartment->next;
        while(position != -1){
            if(position == 0){
                rewind(data_file);
            }else{
                fseek(data_file, customerSize() * position, SEEK_SET);
            }

            TCustomerHash *customer = readCustomer(data_file);

            if(customer->cod == cod){
                fclose(data_file);
                return position;
            }else{
                position = customer->next;
            }
        }

        return -1;
        
    }
}

int insert(TCustomerHash *customer, FILE *hash_file, const char *data_file_name, int size)
{
    int h = hash(customer->cod, size);
    int hash_position = (h) * compartment_size();

    if(hash_position == 0){
        rewind(hash_file);
    }else{
        fseek(hash_file, hash_position, SEEK_SET);
    }

    HashCompartment *compartment = reads_compartment(hash_file);

    if(compartment->next != -1){
        FILE *data_file = fopen(data_file_name, "r+b");

        if(data_file == NULL){
            printf("Error opening data file\n");
            return -1;
        }

        if(compartment->next == 0){
            rewind(data_file);
        }else{
            fseek(data_file, customerSize() * compartment->next, SEEK_SET);
        }

        hash_position = compartment->next;

        while(1){
            CustomerHash *c = readCustomer(data_file);
            if(c->next == -1){
                fseek(data_file, 0, SEEK_END);
                saveCustomer(customer, data_file);
                c->next = fileSize(data_file) -1;

                if(hash_position == 0){
                    rewind(data_file);
                }else{
                    fseek(data_file, customerSize() * hash_position, SEEK_SET);
                }
                saveCustomer(c, data_file);
                free(c);
                fclose(data_file);
                return 1;
            } else{
                fseek(data_file, customerSize() * c->next, SEEK_SET);
                hash_position = c->next;
            }
        }
    }else{
        FILE *data_file;
        if((data_file = fopen(data_file_name, "a+b")) == NULL){
            printf("Error opening data file\n");
            return -1;
        }

        saveCustomer(customer, data_file);

        compartment->next = fileSize(data_file) - 1;
        fseek(hash_file, compartment_size() * (h), SEEK_SET);
        saves_compartment(compartment, hash_file);
        fclose(data_file);
        free(compartment);
        return 1;
    }
}

void print_hash(FILE *hash_file, const char *data_file_name, int size)
{
    for(int i=0;i<size;i++){
        if(i == 0){
            rewind(hash_file);
        }else{
            fseek(hash_file, compartment_size() * i, SEEK_SET);
        }

        HashCompartment *compartment = reads_compartment(hash_file);
        printf("\n\n-> Compartment %d", i+1);


        if(compartment-> next == -1){
            free(compartment);
        }else{
            FILE *data_file = fopen(data_file_name, "r+b");

            if(data_file == NULL){
                printf("Error opening data file\n");
                return;
            }

            if(compartment->next == 0){
                rewind(data_file);
            }else{
                fseek(data_file, customerSize() * compartment->next, SEEK_SET);
            }

            while(1){
                TCustomerHash *customer = readCustomer(data_file);
                printCustomer(customer);
                if(customer->next == -1){
                    break;
                }else{
                    fseek(data_file, customerSize() * customer->next, SEEK_SET);
                }
            }
        }
    }
}

int delete_in_hash(int cod, FILE *hash_file, const char *data_file_name, int size)
{
    int h = hash(cod, size);
    int hash_position = h * compartment_size();

    if(hash_position == 0){
        rewind(hash_file);
    }else{
        fseek(hash_file, hash_position, SEEK_SET);
    }

    HashCompartment *compartment = reads_compartment(hash_file);

    if(compartment->next == -1){
        return -1;
    }else{
        FILE *data_file = fopen(data_file_name, "r+b");

        if(data_file == NULL){
            printf("Error opening data file\n");
            return -1;
        }

        if(compartment->next == 0){
            rewind(data_file);
        }else{
            fseek(data_file, customerSize() * compartment->next, SEEK_SET);
        }

        int position = compartment->next;
        int previous = -1;
        while(position != -1){
            if(position == 0){
                rewind(data_file);
            }else{
                fseek(data_file, customerSize() * position, SEEK_SET);
            }

            TCustomerHash *customer = readCustomer(data_file);

            if(customer->cod == cod){
                if(previous == -1){
                    compartment->next = customer->next;
                    fseek(hash_file, compartment_size() * h, SEEK_SET);
                    saves_compartment(compartment, hash_file);
                }else{
                    fseek(data_file, customerSize() * previous, SEEK_SET);
                    TCustomerHash *previous_customer = readCustomer(data_file);
                    previous_customer->next = customer->next;
                    fseek(data_file, customerSize() * previous, SEEK_SET);
                    saveCustomer(previous_customer, data_file);
                    free(previous_customer);
                }
                free(customer);
                fclose(data_file);
                return 1;
            }else{
                previous = position;
                position = customer->next;
            }
        }
        return -1;
    }
}



