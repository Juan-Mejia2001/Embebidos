#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <vlc/vlc.h>

typedef struct ReproductorMusica ReproductorMusica;

struct ReproductorMusica
{
    libvlc_instance_t *instance; //instancia
    libvlc_media_player_t *mediaPlayer; // reproductor der medios
    libvlc_media_t *media; // archivo de medios
};

ReproductorMusica *ReproductorMusicaNuevo(int argc, const char *const *argv, int cancion){

    const char *music[3] =
    {
        "file:///./music/reggaedrum_01_167a_bytuneloniration.wav",
        "file:///./music/y2mate.com-Morat-Cuando-Nadie-Ve.wav",
        "file:///./music/y2mate.com-Mi-Gente-Hugel-Remix-J-Balvin-Willy-William-Bass-Boosted.wav"
    };

    ReproductorMusica *reproductor = (ReproductorMusica *)
            malloc(sizeof(ReproductorMusica));
    reproductor->instance = libvlc_new(argc, argv);
    reproductor->mediaPlayer = libvlc_media_player_new(reproductor->instance);
    reproductor->media = libvlc_media_new_location(reproductor->instance, music[cancion]);

    return reproductor;
}

void ReproductorMusicaLibera(ReproductorMusica *R)
{
    libvlc_media_release(R->media);
    libvlc_media_player_release(R->mediaPlayer);
    libvlc_release(R->instance);
    free(R);
}

void *reproduceMusica(void *data)
{
    ReproductorMusica *R = (ReproductorMusica *) data;
    libvlc_media_player_set_media(R->mediaPlayer, R->media);
    libvlc_media_parse(R->media);
    libvlc_media_player_play(R->mediaPlayer);
    while (1){}
    return NULL;
}

void *menuPrincipal(void *data)
{
    ReproductorMusica *R = (ReproductorMusica *) data;
    char respuesta = 'n';
    while (respuesta == 'n')
    {
        setbuf(stdin, NULL);
        printf("Quiere quitar la aplicacion? [S/N] "); //S = si / N = no
        scanf("%c", &respuesta);
        if (respuesta == 'S')
        {
            ReproductorMusicaLibera(R);
            exit(EXIT_SUCCESS);

        }

    }
    return NULL;
}

int main(int argc, const char *const *argv)
{
    int cancion;
    printf("1. Reggadrum\n");
    printf("2. Cumbia\n");
    printf("3. Bassbosted\n");
    printf("-> ");
    scanf("%d", &cancion);
    ReproductorMusica *R = ReproductorMusicaNuevo(argc, argv, cancion - 1);
    pthread_t thread1;
    pthread_t thread2;
    pthread_create(&thread1, NULL, &reproduceMusica, R);
    pthread_create(&thread2, NULL, &menuPrincipal, R );
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    return 0;
}
