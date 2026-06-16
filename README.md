# 미스비시 PLC 기반 자동화 교육 키트

미스비시 PLC(Programmable Logic Controller) 기반의 자동화 제어 시스템 및 시뮬레이션 교육 키트입니다. 이 프로젝트는 아두이노를 사용하여 PLC의 기능을 구현하고, 다양한 자동화 제어 로직을 실습할 수 있도록 설계되었습니다.

## 🚀 주요 기능

### 입력 장치
- **푸시 버튼 (Switch)**: 디지털 입력 신호를 테스트합니다.
- **모터 위치 센서 (Encoder)**: 모터의 회전 위치를 정밀하게 감지합니다.
- **실린더 위치 센서**: 공압 실린더의 위치를 감지합니다.

### 출력 장치
- **램프 (Lamp)**: 디지털 출력 상태를 시각적으로 확인합니다.
- **모터 (Motor)**: 회전 운동을 제어합니다.
- **실린더 (Cylinder)**: 직선 운동을 제어합니다.

### 제어 기능
- 디지털/아날로그 입출력 처리
- 모터 제어 (회전 운동)
- 실린더 제어 (직선 운동)
- 인터럽트를 활용한 실시간 위치 감지

## 🛠️ 기술 스택

- **MCU**: ATmega1280 (Arduino Mega)
- **프레임워크**: Arduino

## 📂 프로젝트 구조

- `src/`: 소스 코드 파일
  - `main.cpp`: 메인 프로그램
  - `01_switch_lamp.cpp`: 스위치와 램프 제어
  - `02_motor_control.cpp`: 모터 제어
  - `03_cylinder_control.cpp`: 실린더 제어
  - `04_sensor_cyl.cpp`: 실린더 위치 센서 사용
  - `04_interrupt_encoder.cpp`: 인터럽트를 활용한 엔코더 사용

## ⚙️ 설정

### 플랫폼IO 설정
플랫폼IO 프로젝트 설정을 통해 빌드할 소스 코드를 쉽게 변경할 수 있습니다.

**현재 설정:**
```ini
src_filter = +<main.cpp>
```

**다른 예시:**
- 스위치와 램프 테스트: `src_filter = +<01_switch_lamp.cpp>`
- 모터 제어 테스트: `src_filter = +<02_motor_control.cpp>`
- 실린더 제어 테스트: `src_filter = +<03_cylinder_control.cpp>`
- 실린더 위치 센서 테스트: `src_filter = +<04_sensor_cyl.cpp>`
- 인터럽트 엔코더 테스트: `src_filter = +<04_interrupt_encoder.cpp>`

## 🔌 하드웨어 연결 가이드

...(여기에 하드웨어 핀 연결 정보가 추가될 예정입니다)...