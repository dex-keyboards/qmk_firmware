typedef float (*interpolation_t)(float t);

float flip(float t){
    return 1 - t;
}

float mix(interpolation_t a, interpolation_t b, float t, float mix){
    return a(t) * flip(mix) + b(t) * mix;
}

float crossfade(interpolation_t a, interpolation_t b, float t){
    return mix(a, b, t, t);
}

float smoothStart3(float t){
    return t * t * t;
}

float smoothStop3(float t){
    return flip(smoothStart3(flip(t)));
}

float smoothStep3(float t){
    return crossfade(&smoothStart3, &smoothStop3, t);
}