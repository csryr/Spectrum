#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <math.h>
#include "kissfft/kiss_fft.h"

class Spectrum
{

public:
    sf::RenderWindow &window_;

    Spectrum(sf::RenderWindow &window);

    void wavFFT();

    void loadBuffer(std::string audioFilePath);

    ~Spectrum();

private:
    void dispSpectrum();

    sf::SoundBuffer buffer;
    sf::Sound song;
    sf::Uint64 sampleCount;
    sf::Time fps = sf::milliseconds(31.995);
    const sf::Int16 *samples;

    static const int sampleChunk = 3200;
    int *currentSpectrum = new int[sampleChunk];
    int *prevSpectrum = new int[sampleChunk];
    int *prevPrevSpectrum = new int[sampleChunk];
    int *prevPrevPrevSpectrum = new int[sampleChunk];
    int barsNum = 45;
    int samplesCovered = 0;
    bool check = false;

    kiss_fft_cpx *cx_in = new kiss_fft_cpx[sampleChunk];
    kiss_fft_cpx *cx_out = new kiss_fft_cpx[sampleChunk];
};
