package fr.eseo.poo.projet.artiste.modele;

import static org.junit.Assert.assertEquals;

import org.junit.Test;

public class CoordonneesTest {

	@Test
	public void testConstructeur1() {
		Coordonnees coord1 = new Coordonnees();
		assertEquals("Mauvais x", 0.0, coord1.getAbscisse(), 0.1);
		assertEquals("Mauvais y", 0.0, coord1.getOrdonnee(), 0.1);
	}
	@Test
	public void testConstructeur2() {
		Coordonnees coord1 = new Coordonnees(1.0, 1.0);
		assertEquals("Mauvais x", 1.0, coord1.getAbscisse(), 0.1);
		assertEquals("Mauvais y", 1.0, coord1.getOrdonnee(), 0.1);
	}
	@Test
	public void testGettersSetters() {
		Coordonnees coord1 = new Coordonnees(0.0, 0.0);
		coord1.setAbscisse(2.0);
		coord1.setOrdonnee(2.0);
		assertEquals("Mauvais x", 2.0, coord1.getAbscisse(), 0.1);
		assertEquals("Mauvais y", 2.0, coord1.getOrdonnee(), 0.1);
	}
	
	@Test
	public void testDeplacerde() {
		Coordonnees coord1 = new Coordonnees(1.0, 1.0);
		coord1.deplacerDe(1.0, 1.0);
		assertEquals("Mauvais x", 2.0, coord1.getAbscisse(), 0.1);
		assertEquals("Mauvais y", 2.0, coord1.getOrdonnee(), 0.1);
	}
}







