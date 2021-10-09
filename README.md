# Filters

Filter utilities for Arduino


## Usage

``` C++
#include <Filters.h>
#include <Calculus.h>

Calculus::Integral<float> i;
Calculus::Differential<float> d(10.f);
Filter::LPF<float> l(15.f);
Filter::HPF<float> h(30.f);

void setup() {
    Serial.begin(115200);
    Serial.flush();
    delay(2000);

    Serial.print("sin");      Serial.print(" ");
    Serial.print("int");      Serial.println();
    Serial.print("diff");     Serial.print(" ");
    Serial.print("diff_lpf"); Serial.print(" ");
    Serial.print("diff_hpf"); Serial.println();
}

void loop() {
    float t = millis() / 100.f;
    static float prev_t = t;

    if (t > prev_t + 0.005) {
        float dt = t - prev_t;
        float v = 100.f * sin(t);

        // reset to appropriate value to avoid overshoot
        static bool is_initialized = false;
        if (!is_initialized) {
            i.reset(v);
            d.reset(v);
        }
        float v_i = i.get(v, dt);
        float v_d = d.get(v, dt);

        // reset to appropriate value to avoid overshoot
        if (!is_initialized) {
            l.reset(v_d);
            h.reset(v_d);
        }
        float v_dl = l.get(v_d, dt);
        float v_dh = h.get(v_d, dt);

        Serial.print(v);    Serial.print(" ");
        Serial.print(v_i);  Serial.print(" ");
        Serial.print(v_d);  Serial.print(" ");
        Serial.print(v_dl); Serial.print(" ");
        Serial.print(v_dh); Serial.println();

        prev_t = t;
        is_initialized = true;
    }
}
```


## Embedded Libraries

- [ArxTypeTraits v0.2.3](https://github.com/hideakitai/ArxTypeTraits)


## License

MIT
