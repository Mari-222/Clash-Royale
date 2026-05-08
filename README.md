# Clash-Royale
Sistema de Gestión Clash Royale
Curso: Estructuras de Datos
Fecha: Mayo 2026

Descripción
Sistema de simulación y gestión inspirado en Clash Royale, desarrollado en C++.
Administra cartas, jugadores, mazos, clanes, arenas y batallas mediante listas dinámicas construidas desde cero, sin uso de la STL.

Integrantes
Mari-222
Josue507Julio
billo08

Estructuras utilizadas
Cartas:Lista simple (inserción al inicio)
Jugadores: Lista doble ordenada alfabéticamente
Mazos: Lista simple (inserción al final)
Clanes: Lista circular (inserción al final)
Arenas: Lista simple (inserción al inicio)
Batallas: Lista doble circular (inserción al final)

Operaciones disponibles por entidad
Cada entidad soporta las siguientes operaciones: inserción con validaciones, modificación, eliminación y búsqueda por ID. 
Las sublistas de cartas en mazos y jugadores en clanes también permiten inserción y eliminación individual.

Validaciones implementadas
Unicidad de IDs en todas las entidades
Costo de elixir entre 1 y 9
Trofeos del jugador compatibles con el rango de su arena
Mazos con exactamente 8 cartas sin repetición
Mazos pertenecientes al jugador correcto en batallas
Coronas entre 0 y 3
Un jugador solo puede pertenecer a un clan
Sin solapamiento de rangos entre arenas

Consultas
Carta más utilizada en todos los mazos
Jugador con más trofeos
Clan con más miembros
Mazo con menor costo promedio de elixir
Arena con más jugadores
Jugador con más victorias
Batallas realizadas en una arena determinada
Jugadores de un clan específico
Cartas de rareza legendaria
Mazos de un jugador determinado

Reportes
Todas las listas principales
Detalle de cada jugador con su arena, clan y mazos
Mazos con sus 8 cartas
Clanes con sus miembros
Arenas con sus jugadores
Batallas con detalle completo
Cartas ordenadas por costo de elixir
Jugadores en orden alfabético
Victorias por jugador

Simulación de batallas
Calcula automáticamente el ganador basándose en el poder ofensivo y defensivo de cada mazo. Registra la batalla con estadísticas de promedio de elixir, tipo predominante de cartas y ciclos de elixir estimados.

Carga automática de datos
Al iniciar el sistema se cargan automáticamente 10 registros por cada entidad principal mediante datos definidos en código, sin lectura de archivos.
