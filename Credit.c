#include <stdio.h>

// Função para calcular a soma dos dígitos de um número
int sum_digits(int number)
{
    int sum = 0;
    while (number > 0)
    {
        sum += number % 10; // Adiciona o último dígito à soma
        number /= 10; // Remove o último dígito
    }
    return sum;
}

// Função para ler um número inteiro positivo
long get_positive_long(const char *prompt)
{
    long number;
    while (1) // Loop infinito até que a entrada seja válida
    {
        printf("%s", prompt); // Exibe a mensagem solicitando a entrada
        if (scanf("%ld", &number) == 1 && number > 0) // Verifica se a entrada é válida
        {
            break; // Sai do loop se a entrada for válida
        }
        // Limpa o buffer de entrada em caso de entrada inválida
        while (getchar() != '\n'); // Descarta caracteres extras
        printf("Entrada inválida. Digite um número positivo.\n");
    }
    return number;
}

int main(void)
{
    // Solicita o número do cartão ao usuário
    long card_number = get_positive_long("Número do cartão: ");

    // Verifica o comprimento e o tipo do cartão
    int length = 0;
    long temp = card_number;
    while (temp > 0)
    {
        temp /= 10;
        length++;
    }

    // Verifica se o comprimento é válido
    if (length != 13 && length != 15 && length != 16)
    {
        printf("INVALID\n");
        return 0;
    }

    // Aplica o algoritmo de Luhn
    int sum = 0;
    temp = card_number;
    for (int i = 1; i <= length; i++)
    {
        int digit = temp % 10;
        if (i % 2 == 0) // Dígitos pares (segundo a partir do final)
        {
            sum += sum_digits(digit * 2); // Multiplica por 2 e soma os dígitos
        }
        else // Dígitos ímpares
        {
            sum += digit;
        }
        temp /= 10;
    }

    // Verifica se o número é válido
    if (sum % 10 != 0)
    {
        printf("INVALID\n");
        return 0;
    }

    // Identifica o tipo do cartão
    long first_two_digits = card_number;
    while (first_two_digits >= 100)
    {
        first_two_digits /= 10;
    }

    if ((first_two_digits == 34 || first_two_digits == 37) && length == 15)
    {
        printf("AMEX\n");
    }
    else if ((first_two_digits >= 51 && first_two_digits <= 55) && length == 16)
    {
        printf("MASTERCARD\n");
    }
    else if ((first_two_digits / 10 == 4) && (length == 13 || length == 16))
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }

    return 0;
}
