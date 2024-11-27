#include "Star.h"

void Star::draw() const {
    if ((center.x - R <= rt.left) || (center.x + R >= rt.right) || (center.y - R <= rt.top) || (center.y + R >= rt.bottom))
        throw BorderException{ "����� �� ������� ����.������������� ������: ���������� ������(" + std::to_string(center.x) + ", "
        + std::to_string(center.y) + "), ���������� ������: " + std::to_string(r) + ", ������� ������: " + std::to_string(R) };

    if (r >= R)
        throw IncorrectRadius{ "���������� ������ ������ ��������: ������������� ������: ���������� ������: " + std::to_string(r) + ", ������� ������: " + std::to_string(R)};

    
    if (r<=0 && R<=0)
        throw NegativeNumber{ "������� ��� ������������� �������� ����������.������������� ������: ���������� ������(" + std::to_string(center.x)
        + ", " + std::to_string(center.y) + "), ���������� ������: " + std::to_string(r) + ", ������� ������: " + std::to_string(R) };


    HPEN pen = CreatePen(PS_SOLID, 3, color_pen);
    HBRUSH brush = CreateSolidBrush(color_figure);

    SelectObject(hdc, pen);
    SelectObject(hdc, brush);

    POINT points[12];
    float alpha = 0;
    for (int i = 0; i < 2 * 6; i++) {
        const double PI = 3.141592653589793;
        int l = i % 2 == 0 ? r : R;
        points[i].x = center.x + l * cos(alpha);
        points[i].y = center.y + l * sin(alpha);
        alpha += PI / 6;
    }
    Polygon(hdc, points, 12);

    DeleteObject(pen);
    DeleteObject(brush);
    DeletePen(pen);
    DeleteBrush(brush);

}

void Star::hide() const {
    HPEN pen = CreatePen(PS_SOLID, 3, GetBkColor(hdc));
    HBRUSH brush = CreateSolidBrush(GetBkColor(hdc));

    SelectObject(hdc, pen);
    SelectObject(hdc, brush);

    POINT points[12];
    float alpha = 0;
    for (int i = 0; i < 2 * 6; i++) {
        const double PI = 3.141592653589793;
        int l = i % 2 == 0 ? r : R;
        points[i].x = center.x + l * cos(alpha);
        points[i].y = center.y + l * sin(alpha);
        alpha += PI / 6;
    }
    Polygon(hdc, points, 12);


    DeleteObject(pen);
    DeleteObject(brush);
    DeletePen(pen);
    DeleteBrush(brush);

}


void Star::move(int dx, int dy) {
    hide();
    center.x += dx;
    center.y += dy;
    draw();
}