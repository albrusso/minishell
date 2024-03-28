/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 14:46:58 by albrusso          #+#    #+#             */
/*   Updated: 2024/03/28 18:30:59 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
char *strjoin(const char *s1, const char *s2) {
    size_t len1 = strlen(s1);
    size_t len2 = strlen(s2);
    char *result = malloc(len1 + len2 + 1);
    if (result == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

char *try_expand(const char *const env[], char *s) {
    char *result = NULL; // Stringa risultante
    size_t s_len = strlen(s); // Lunghezza della stringa di input

    // Ciclo fino a quando non si raggiunge il terminatore di stringa
    for (size_t i = 0; i < s_len; ++i) {
        if (s[i] == '$') {
            // Se troviamo un '$', proviamo a espandere la variabile di ambiente
            size_t start = i + 1; // Indice del carattere successivo a '$'
            size_t end = start;   // Indice del primo carattere dopo il nome della variabile
            while (s[end] && s[end] != '$' && s[end] != '\0') {
                ++end; // Spostiamoci al prossimo carattere
            }

            // Se abbiamo trovato un nome di variabile, proviamo a espanderlo
            if (start != end) {
                // Estraiamo il nome della variabile
                size_t var_len = end - start;
                char var_name[var_len + 1];
                memcpy(var_name, &s[start], var_len);
                var_name[var_len] = '\0';

                // Cerchiamo il valore della variabile nell'array env
                for (int j = 0; env[j] != NULL; ++j) {
                    // Controllo se il nome della variabile coincide
                    size_t len = strcspn(env[j], "=");
                    if (len == var_len && strncmp(env[j], var_name, len) == 0) {
                        // Abbiamo trovato la variabile, quindi espandiamola
                        char *env_value = env[j] + len + 1;
                        result = strjoin(result ? result : "", env_value);
                        i = end - 1; // Spostiamo l'indice al primo carattere dopo il nome della variabile
                        break;
                    }
                }
                // Se la variabile non è stata trovata, copiamo la parte non espandibile nella stringa risultante
                if (result == NULL) {
                    char substr[end - i];
                    memcpy(substr, &s[i], end - i);
                    substr[end - i] = '\0';
                    result = strjoin(result ? result : "", substr);
                    i = end - 1; // Spostiamo l'indice al primo carattere dopo il nome della variabile
                }
            } else {
                // Se abbiamo trovato solo '$', copiamo '$' nella stringa risultante
                result = strjoin(result ? result : "", "$");
            }
        } else {
            // Copiamo i caratteri non riguardanti le variabili di ambiente
            char str[2] = {s[i], '\0'};
            result = strjoin(result ? result : "", str);
        }
    }

    return result;
}
void	expander(t_data *d, t_lexer **lex)
{
	t_lexer	*tmp;
	char	*tmp1;

	tmp = *lex;
	while (tmp)
	{
		if (ft_strchr(tmp->s, '$'))
		{
			tmp1 = ft_strdup(tmp->s);
			free(tmp->s);
			tmp->s = try_expand(d->env, tmp1);
			free(tmp1);
		}
		tmp = tmp->n;
	}
	
}